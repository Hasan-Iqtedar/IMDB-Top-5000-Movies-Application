
/*
 * Hasan Iqtedar - BSCS 9A
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

//Total number of movies in the dataset.
#define NumMovies 5043

/*********************Prototypes*********************/
class Movie;
class Actor;
class Director;

template<typename dtype>
class Node;//Generic Node class for lists and stacks.

template<typename dtype>
class Stack;

template <typename dtype>
class MovieList;//Singly linked list for movies.

template <typename dtype>
class ActorList;//Singly linked list for actors.

template <typename dtype>
class DirectorList;//Singly linked list for directors.

class GenreList;//Singly linked list for genres of a movie.

class PlotKeywordsList;//Singly linked list for plot keywords of a movie.

class IndexedMovieList;//A class to store Indexed movie Lists by year, rating and genre.

class IndexedByGenre;//A class to maintain movie indexes w.r.t genre.

//A method to parse a line of a csv file.
vector<string> parseCsvFile(fstream&);

//A method to extract all the data from the dataset into the data structures.
void extractData(MovieList<Movie>*, ActorList<Actor>*, DirectorList<Director>*,
	IndexedMovieList*, IndexedMovieList*, IndexedByGenre*);

//---------------------------------------------------------------------------------------
/********************************Start of main classes**********************************/


/***********************Node Class*************************/

/*
 *Generic Node class for
 *MovieNode, ActorNodes, DirectorNodes
 *PointerNodes to Movies, Actors and Directors.
 *Genres list and plot_keywords list.
*/
template<typename dtype>
class Node {
public:
	dtype data;
	Node* next;

	//Default Constructor.
	Node() {
		next = NULL;
	}


};//End of class Node.



/*MovieList is made up of MovieNodes that contain objects of Movie in data
 *part and address of next MovieNode in the next part for movieList.
 *Costructor of class Movie takes a vector with values for
 *all the fields of this class and initializes the object with
 *those values. Movies are insertedByTitle in the movieList.
 */
class Movie {
public:
	/*Fields*/
	string title;
	string movie_imdb_link;
	string content_rating;

	//Linked list of genres for a movie.
	GenreList* genre;

	//Linked list of plot keywords for a movie.
	PlotKeywordsList* plot_keywords;

	string language;
	string country;

	unsigned short int title_year;
	unsigned short int num_critic_for_reviews;
	unsigned short int duration;
	unsigned short int facenumber_in_poster;
	unsigned short int num_user_for_reviews;

	unsigned int gross;
	unsigned int num_voted_users;
	unsigned int cast_total_facebook_likes;
	unsigned int movie_facebook_likes;

	long long int budget;
	//unsigned int budget;

	float imdb_score;
	float aspect_ratio;

	//ActorList of ActorNodes with pointer to an actor in data part.
	ActorList<Actor*>* actors;

	//Pointer to the director in directorList.
	Director* director;

	bool color;

	//Default Constructor
	Movie() {
		genre = NULL;
		actors = NULL;
		director = NULL;
		plot_keywords = NULL;
	}

	/*Constructor to initialize fields*/
	Movie(vector<string> vector) {

		try {

			title = vector[0];
			language = vector[22];
			country = vector[23];
			//vector[1] is a special symbol a'.

			imdb_score = stof(vector[4]);
			movie_imdb_link = vector[20];
			content_rating = vector[24];
			aspect_ratio = stof(vector[26]);

			/*These are updated in main like in Actor and Director*/
			genre = NULL;
			actors = NULL;
			director = NULL;
			plot_keywords = NULL;

			gross = unsigned int(stoi(vector[15]));
			budget = long long int(stoll(vector[25]));
			num_voted_users = unsigned int(stoi(vector[16]));
			movie_facebook_likes = unsigned int(stoi(vector[27]));


			duration = unsigned short int(stoi(vector[8]));
			title_year = unsigned short int(stoi(vector[3]));
			facenumber_in_poster = unsigned short int(stoi(vector[18]));
			num_user_for_reviews = unsigned short int(stoi(vector[21]));
			num_critic_for_reviews = unsigned short int(stoi(vector[7]));
			cast_total_facebook_likes = unsigned int(stoi(vector[17]));


			if ((vector[28]) == "color")
				color = true;
			else
				color = false;


		}//End of try clause.

		catch (invalid_argument ex) {
			cout << ex.what() << endl;
		}

	}//And of Mr. Constructor.




};//End of class Movie.


/*Actor class for storing data of an actor.
 *ActorList is made up of ActorNodes which have objects of Actor
 *class in their data part.
*/
class Actor {
public:
	string name;
	unsigned short int facebook_likes;
	//This is a pointer to the start of the moviesActedInList.
	MovieList<Movie*>* moviesActedIn;

	//Default construction.
	Actor() {
		moviesActedIn = NULL;
	}

	//Constructor.
	Actor(string name, unsigned short int fbLikes) {
		this->name = name;
		facebook_likes = fbLikes;
	}

};//End of class Actor.


/*Director class for storing data of a director.
 *DirectorList is made up of DirectorNodes which have objects
 *of Director class in data part.
*/
class Director {
public:
	string name;
	unsigned short int facebook_likes;
	MovieList<Movie*>* MoviesDirected;//A pointer to the start of the MoviesDirectedList.

	//Default construction.
	Director() {
		MoviesDirected = NULL;
	}

	//Constructor.
	Director(string name, unsigned short int fbLikes) {
		this->name = name;
		facebook_likes = fbLikes;
	}

};//End of class Director.


/*Stack is used to display the contents of a list in reverse.*/
template<typename dtype>
class Stack {
public:
	int top;
	int size;
	dtype* stack;

	Stack(int size) {
		top = -1;
		this->size = size;
		stack = new dtype[size];
	}

	bool isEmpty() {
		return top == -1;
	}

	bool isFull() {
		return top == size - 1;
	}

	/*Inserts an element at the top of the stack.*/
	void Push(dtype value) {

		if (isFull()) {
			cout << "Stack is full.\n";
			return;
		}

		top++;
		stack[top] = value;
	}//End of method Push.

	/*Pops and returns top element from the stack. Call only when the stack is not empty.*/
	dtype Pop() {

		//Removing the element.
		top--;

		//Returning the popped element.
		return stack[top + 1];
	}//End of method Pop.


	/*Deletes the content stored in the stack.*/
	void DestroyStack() {

		top = -1;
		size = 0;
		delete stack;

	}//End of method DestroyStack.


};//End of class Stack



/********************Linked list classes********************/


/*Used when searching for unique co-actors of an actor in actorlist.
* Each co-actor is inserted in the list and every new co-actor is
  first checked if it is already in the list or not.
* Nodes are of type string which contain a name in the data part.
*/
class UniqueCoactorsList {
public:
	Node<string>* start;
	Node<string>* last;
	Node<string>* loc;
	Node<string>* pLoc;

	//Default Constructor.
	UniqueCoactorsList() {
		start = NULL;
		last = NULL;
		loc = NULL;
		pLoc = NULL;
	}

	/*Searches the logical position by name.
	* Updates loc and pLoc accordingly.
	* Worst case time complexity is O(n). 
	* Best case complexity is constant.
	*/
	void SearchByName(string name) {

		//If list is empty.
		if (start == NULL)
			return;

		loc = start;
		pLoc = NULL;

		while (loc != NULL && loc->data < name) {
			pLoc = loc;
			loc = loc->next;
		}

		//If not found.
		if (loc != NULL && loc->data != name)
			loc = NULL;

	}//End of method SearchByName.


	/*Inserts a name at its logical position
	* Worst case time complexity is O(1). Not counting the search operation.
	* Best case complexity is also constant.
	*/
	void InsertSorted(string name) {

		SearchByName(name);

		//If found.
		if (loc != NULL)
			return;

		Node<string>* newNode = new Node<string>();
		newNode->data = name;

		//If actor is not in list.
		if (pLoc == NULL) {//Position should be at start.
			if (start == NULL)
				last = newNode;
			else
				newNode->next = start;

			start = newNode;
		}

		else if (pLoc == last) {//Position should be at last.
			last->next = newNode;
			last = newNode;
		}
		else {//Position is in-between.
			newNode->next = pLoc->next;
			pLoc->next = newNode;
		}


	}//End of method InsertSorted.


	/*Destroys the list.
	* Worst case time complexity is O(n).
	* Best case complexity is also linear.
	*/
	void DestroyList() {

		Node<string>* temp;

		while (start != NULL) {
			temp = start;
			start = start->next;
			delete temp;

		}

		last = NULL;

	}//End of method DestroyList.


};//End of class UniqueCoactorsList.



/*Singly linked list for movies.
 *dtype can be Movie for a list of MovieNodes with movies in data part.
 *or Movie* for a list of MovieNodes with pointer to movies in data part.
 */
template <typename dtype>
class MovieList {
public:
	Node<dtype>* start;
	Node<dtype>* last;
	Node<dtype>* loc;
	Node<dtype>* pLoc;

	Movie* lastMovieInserted;

	//Constructor to initialize fields.
	MovieList() {
		start = NULL;
		last = NULL;
		loc = NULL;
		pLoc = NULL;

		lastMovieInserted = NULL;
	}

	bool IsEmpty() {
		return start == NULL;
	}


	/******************Methods for list of movie nodes******************/


	/*To search the logical position of a Movie by title.
	* Takes the movie title to be searched as argument and modifies
	* loc and pLoc accordingly.
	* pLoc = NULL implies position should be at start.
	* pLoc = Last imples position should be at last.
	* loc = start imples value found at head node.
	* loc = last imples calue found at last node.
	* loc = NULL implies value not found but pLoc suggests logical position.
	* Worst case time complexity is O(n).
	* Best case complexity is constant.
	*/
	void SearchByTitle(string title) {

		//loc may not be at start and pLoc may not be NULL.
		loc = start;
		pLoc = NULL;

		if (IsEmpty())
			return;


		while (loc != NULL && loc->data.title < title) {
			pLoc = loc;
			loc = loc->next;
		}

		//If value not found and loc is not NULL.
		if (loc != NULL && loc->data.title != title)
			loc = NULL;


	}//End of method SearchByTitle.


	/*To insert a movie at its logical position by title.
	* Takes a movie as argument and inserts it at it's logical position.
	* Assuming ascending order A-Z;
	* Worst case time complexity is O(1) not counting the search operation used.
	* Best case complexity is also constant.
	*/
	void InsertByTitle(Movie movie) {

		SearchByTitle(movie.title);

		//If movie is already in the list.
		if (loc != NULL)
			return;

		Node<Movie>* newNode = new Node<Movie>();
		newNode->data = movie;

		//If movie is not in the list.
		if (pLoc == NULL) {//Position should be at start.
			if (IsEmpty()) {
				last = newNode;
			}
			else
				newNode->next = start;

			start = newNode;

		}
		else if (pLoc == last) {//Position should be at last.
			last->next = newNode;
			last = newNode;
		}
		else {//Position is in-between.
			newNode->next = pLoc->next;
			pLoc->next = newNode;
		}

		lastMovieInserted = &(newNode->data);

	}//End of method InsertByTitle.


	/*FOR LIST OF MOVIE NODES ONLY.
	* Prints the titles of the movie list.
	* Worst case time complexity is O(n).
	* Best case complexity is also linear.
	*/
	void PrintList() {

		if (IsEmpty())
			return;

		Node<Movie>* temp = start;
		while (temp != NULL) {
			cout << temp->data.title << endl;
			temp = temp->next;
		}

	}



	/******************Methods for list of pointer movie nodes******************/

	/* FOR MAINTAINING YEAR-WISE SORTED LIST ONLY.
	* Searches the logical position of a Movie by year.
	* Takes the movie year to be searched as argument and modifies
	* loc and pLoc accordingly.
	* Duplicates are also accomodated.
	* If a year is already present then another movie with
	* same year will also have that same location.
	* And in indexed list, it will be inserted as predecessor
	* of the movie already present.
	* Worst case time complexity is O(n).
	* Best case complexity is also linear.
	*/
	void SearchByYear(unsigned short int year) {

		//loc may not be at start and pLoc may not be NULL.
		loc = start;
		pLoc = NULL;

		if (IsEmpty())
			return;

		while (loc != NULL && loc->data->title_year < year) {
			pLoc = loc;
			loc = loc->next;
		}

		//If value is not found.
		if (loc != NULL and loc->data->title_year != year)
			loc = NULL;


	}//End of method SearchByYear.


	/*FOR MAINTAINING RATING-WISE SORTED LIST ONLY.
	* Searches the logical position of a Movie by rating.
	* Takes the movie rating to be searched as argument and modifies
	* loc and pLoc accordingly.
	* Duplicates are also accomodated.
	* If a rating is already present then another movie with
	* same rating will also have that same location.
	* And in indexed list, it will be inserted as predecessor
	* of the movie already present.
	* Worst case time complexity is O(n).
	Best case complexity is also linear.
	*/
	void SearchByRating(float rating) {

		//loc may not be at start and pLoc may not be NULL.
		loc = start;
		pLoc = NULL;

		if (IsEmpty())
			return;

		while (loc != NULL && loc->data->imdb_score < rating) {
			pLoc = loc;
			loc = loc->next;
		}

		if (loc != NULL && loc->data->imdb_score != rating)
			loc = NULL;

	}//End of method SearchByRating.


	/*To insert a movie pointer for year or rating-wise sorted indexed movie list.
	* Takes the address of the movie to be inserted as argument.
	* If loc not NULL. I.e. a movie with the same title is already present,
	* then new movie pointer is inserted as the predecessor of that movie's pointer.
	* Takes the mode of insertion as argument.
	* Default mode is "year" i.e Insertion for year-wise sorted list.
	* Worst case time complexity is O(1) not counting the searching operation used.
	* Best case complexity is also constant.
	*/
	void InsertByYearOrRating(Movie* pmovie, string mode = "year") {

		if (mode == "year")
			SearchByYear(pmovie->title_year);
		else
			SearchByRating(pmovie->imdb_score);


		Node<Movie*>* newNode = new Node<Movie*>();
		newNode->data = pmovie;

		if (IsEmpty()) {
			start = newNode;
			last = newNode;
		}
		else if (pLoc == NULL) {
			newNode->next = start;
			start = newNode;
		}
		else if (pLoc == last) {
			last->next = newNode;
			last = newNode;
		}

		else {//Whether loc is NULL or not.
			newNode->next = pLoc->next;
			pLoc->next = newNode;
		}


	}//End of method InsertByYearOrRating.



	/**********************Operations Implementations**********************/


	/*To find a movie using its title.
	* Takes title of the movie as input.
	* Worst case time complexity is O(1) not counting the search operation.
	* Best case complexity is also constant.
	*/
	void FindMovie(string title) {

		SearchByTitle(title);

		if (loc == NULL) {
			cout << "Movie not found" << endl;
			return;
		}

		cout << "\nTitle: " << loc->data.title << endl;
		cout << "Release year: " << loc->data.title_year << endl;
		cout << "Rating: " << loc->data.imdb_score << endl;
		cout << "Budget: " << loc->data.budget << endl;
		cout << "Duration: " << loc->data.duration << endl;
		cout << "Director: " << loc->data.director->name << endl;
		cout << "Gross: " << loc->data.gross << endl;

		cout << "Actors are :\n";
		cout << loc->data.actors->start->data->name << " | ";
		cout << loc->data.actors->start->next->data->name << " | ";
		cout << loc->data.actors->start->next->next->data->name << endl;

		cout << "Genres are:\n";
		loc->data.genre->PrintList();

	}//End of method FindMovie.


	/*

	* Operation 9 - to search movies in a given year is implemented in IndexedMovieList
	  class below where its name is FindMoviesInYear.

	* Operation 10 - to display movies year-wise in increasing or decreasing order is
	  also implemented in IndexedMovieList class below where its name is PrintByYear.

	* Operation 12 - to display movies rating-wise in increasing or decreasing order is
	  also implemented in IndexedMovieList class below where its name is PrintByRating.

	* Operation 11 - to display movies of specified genre rating-wise is
	  implemented in IndexedByGenre class below

	*/


};//End of class MovieList.



/*Indexes of different sorting versions of Movies are maintained here.
* This class contains two movieLists of pointer nodes.
* These include sorted by year and sorted by rating.
*/
class IndexedMovieList {
public:

	MovieList<Movie*>* indexedByYear;
	MovieList<Movie*>* indexedByRating;//imdb_score.

	//Constructor.
	IndexedMovieList() {
		indexedByYear = new MovieList<Movie*>();
		indexedByRating = new MovieList<Movie*>();
	}

	/*To find all the movies released in a given year.
	* Takes the year as an argument.
	* Displays all movies released in that year.
	* Worst case time complexity = O(n) where n = No. of movies of specified year.
	  (Not counting the searching method used inside)
	* Best case complexity is also the same. 
	*/
	void FindMoviesInYear(unsigned short int year) {

		indexedByYear->SearchByYear(year);

		if (indexedByYear->loc == NULL) {
			return;
		}

		Node<Movie*>* temp = indexedByYear->loc;

		while (temp->data->title_year == year) {
			cout << temp->data->title << " | " << temp->data->title_year << endl;
			temp = temp->next;
		}


	}//End of method FindMoviesInYear.


	/*Displays all the movies year-wise.
	* Takes pointer of indexedByYear list above, and order (increasing or decreasing) as argument.
	* Default order is increasing.
	* Worst case time complexity is O(n) where n = total no. of movies.
	* Best case complexity is also the same.
	*/
	void PrintByYear(Node<Movie*>* temp, string order = "increasing") {

		if (order == "increasing") {

			while (temp != NULL) {
				cout << temp->data->title << " | " << temp->data->title_year << endl;
				temp = temp->next;
			}

		}

		else {

			Stack<Node<Movie*>*>* stack = new Stack<Node<Movie*>*>(NumMovies);
 
			//Pushing all the movie pointers on the stack.
			while (temp != NULL) {
				stack->Push(temp);
				temp = temp->next;
			}

			//Poping all the pointers and displaying movies by year in decresing order. 
			while (!stack->isEmpty()) {
				temp = stack->Pop();
				cout << temp->data->title << " | " << temp->data->title_year << endl;
			}

			stack->DestroyStack();
		}


	}//End of method PrintByYear.


	/*Displays all the movies rating-wise.
	* Takes pointer of indexedByRating list above, and order (increasing or decreasing) as argument.
	* Default order is increasing.
	* Worst case time complexity is O(n) where n = total no. of movies.
	* Best case complexity is also the same.
	*/
	void PrintByRating(Node<Movie*>* temp, string order = "increasing") {
		
		if (order == "increasing") {

			while (temp != NULL) {
				cout << temp->data->title << " | " << temp->data->imdb_score << endl;
				temp = temp->next;
			}

		}

		else {

			Stack<Node<Movie*>*>* stack = new Stack<Node<Movie*>*>(NumMovies);

			//Pushing all the movie pointers on the stack.
			while (temp != NULL) {
				stack->Push(temp);
				temp = temp->next;
			}

			//Poping all the pointers and displaying movies by rating in decresing order. 
			while (!stack->isEmpty()) {
				temp = stack->Pop();
				cout << temp->data->title << " | " << temp->data->imdb_score << endl;
			}

			stack->DestroyStack();

		}

	}//End of method PrintByRating.


	/*Destroys both indexedByYear and indexedByRating lists.
	* Worst case time complexity is O(n+m) where n = length of indexedByYear list
	  and m = length of indexedByRating list.
	* Because n and m can be different depending upon usage.
	* Best case complexity is also the same.
	*/
	void DestroyList() {

		Node<Movie*>* temp; //= indexedByRating->start;

		//Destroying indexedByRating list.
		while (indexedByRating->start != NULL) {
			temp = indexedByRating->start;
			indexedByRating->start = indexedByRating->start->next;
			delete temp;
		}//End of while loop.

		//Destroying indexedByYear list.
		while (indexedByYear->start != NULL) {
			temp = indexedByYear->start;
			indexedByYear->start = indexedByYear->start->next;
			delete temp;
		}//End of while loop.

	}


};//End of class IndexedMovieList.



/*MovieList of pointer to Movie Nodes sorted by each genre.
 * A huge list of movie pointers is maintained for each genre.
 * Record of each genre is kept using specific pointers for each genre available.
 * Total 26 genres are available.
 */
class IndexedByGenre {
public:
	Node<Movie*>* start;

	/*26 pointer fields for 26 genres*/
	Node<Movie*>* Action;
	Node<Movie*>* Adventure;
	Node<Movie*>* Fantasy;
	Node<Movie*>* Sci_Fi;
	Node<Movie*>* Thriller;
	Node<Movie*>* Documentary;
	Node<Movie*>* Romance;
	Node<Movie*>* Animation;
	Node<Movie*>* Comedy;
	Node<Movie*>* Family;
	Node<Movie*>* Musical;
	Node<Movie*>* Mystery;
	Node<Movie*>* Western;
	Node<Movie*>* Drama;
	Node<Movie*>* History;
	Node<Movie*>* Sport;
	Node<Movie*>* Crime;
	Node<Movie*>* Horror;
	Node<Movie*>* War;
	Node<Movie*>* Biography;
	Node<Movie*>* Music;
	Node<Movie*>* Game_Show;
	Node<Movie*>* Reality_TV;
	Node<Movie*>* News;
	Node<Movie*>* Short;
	Node<Movie*>* Film_Noir;

	//Default Constructor.
	IndexedByGenre() {
	}

	bool IsEmpty() {
		return start == NULL;
	}


	/*Inserts a movie pointer at its logaical location with respect to
	* the specified genre.
	* Worst case time complexity is O(1) i.e constant.
	* Best case complexity is also the same.
	*/
	void InsertByGenre(string genre, Movie* pmovie) {

		Node<Movie*>* newNode = new Node<Movie*>();
		newNode->data = pmovie;

		if (IsEmpty()) {
			start = newNode;
		}

		if (genre == "Action") {

			//If it is the first action movie.
			if (Action != NULL) {
				newNode->next = Action->next;
				Action->next = newNode;
			}
			else {
				Action = newNode;
			}
			Action = newNode;
		}

		else if (genre == "Adventure") {

			if (Adventure != NULL) {
				newNode->next = Adventure->next;
				Adventure->next = newNode;
			}
			else {
				Adventure = newNode;
				Action->next = Adventure;
			}
			Adventure = newNode;
		}

		else if (genre == "Fantasy") {

			if (Fantasy != NULL) {
				newNode->next = Fantasy->next;
				Fantasy->next = newNode;
			}
			else {
				Fantasy = newNode;
				Adventure->next = Fantasy;
			}
			Fantasy = newNode;
		}

		else if (genre == "Sci-Fi") {

			if (Sci_Fi != NULL) {
				newNode->next = Sci_Fi->next;
				Sci_Fi->next = newNode;
			}
			else {
				Sci_Fi = newNode;
				Fantasy->next = Sci_Fi;
			}
			Sci_Fi = newNode;
		}

		else if (genre == "Thriller") {

			if (Thriller != NULL) {
				newNode->next = Thriller->next;
				Thriller->next = newNode;
			}
			else {
				Thriller = newNode;
				Sci_Fi->next = Thriller;
			}
			Thriller = newNode;
		}

		else if (genre == "Documentary") {

			if (Documentary != NULL) {
				newNode->next = Documentary->next;
				Documentary->next = newNode;
			}
			else {
				Documentary = newNode;
				Thriller->next = Documentary;
			}
			Documentary = newNode;
		}

		else if (genre == "Romance") {

			if (Romance != NULL) {
				newNode->next = Romance->next;
				Romance->next = newNode;
			}
			else {
				Romance = newNode;
				Documentary->next = Romance;
			}
			Romance = newNode;
		}

		else if (genre == "Animation") {

			if (Animation != NULL) {
				newNode->next = Animation->next;
				Animation->next = newNode;
			}
			else {
				Animation = newNode;
				Romance->next = Animation;
			}
			Animation = newNode;
		}

		else if (genre == "Comedy") {

			if (Comedy != NULL) {
				newNode->next = Comedy->next;
				Comedy->next = newNode;
			}
			else {
				Comedy = newNode;
				Animation->next = Comedy;
			}
			Comedy = newNode;
		}

		else if (genre == "Family") {

			if (Family != NULL) {
				newNode->next = Family->next;
				Family->next = newNode;
			}
			else {
				Family = newNode;
				Comedy->next = Family;
			}
			Family = newNode;
		}

		else if (genre == "Musical") {

			if (Musical != NULL) {
				newNode->next = Musical->next;
				Musical->next = newNode;
			}
			else {
				Musical = newNode;
				Family->next = Musical;
			}
			Musical = newNode;
		}

		else if (genre == "Mystery") {

			if (Mystery != NULL) {
				newNode->next = Mystery->next;
				Mystery->next = newNode;
			}
			else {
				Mystery = newNode;
				Musical->next = Mystery;
			}
			Mystery = newNode;
		}

		else if (genre == "Western") {

			if (Western != NULL) {
				newNode->next = Western->next;
				Western->next = newNode;
			}
			else {
				Western = newNode;
				Mystery->next = Western;
			}
			Western = newNode;
		}

		else if (genre == "Drama") {

			if (Drama != NULL) {
				newNode->next = Drama->next;
				Drama->next = newNode;
			}
			else {
				Drama = newNode;
				Western->next = Drama;
			}
			Drama = newNode;
		}

		else if (genre == "History") {

			if (History != NULL) {
				newNode->next = History->next;
				History->next = newNode;
			}
			else {
				History = newNode;
				Drama->next = History;
			}
			History = newNode;
		}

		else if (genre == "Sport") {

			if (Sport != NULL) {
				newNode->next = Sport->next;
				Sport->next = newNode;
			}
			else {
				Sport = newNode;
				History->next = Sport;
			}
			Sport = newNode;
		}

		else if (genre == "Crime") {

			if (Crime != NULL) {
				newNode->next = Crime->next;
				Crime->next = newNode;
			}
			else {
				Crime = newNode;
				Sport->next = Crime;
			}
			Crime = newNode;
		}

		else if (genre == "Horror") {

			if (Horror != NULL) {
				newNode->next = Horror->next;
				Horror->next = newNode;
			}
			else {
				Horror = newNode;
				Crime->next = Horror;
			}
			Horror = newNode;
		}

		else if (genre == "War") {

			if (War != NULL) {
				newNode->next = War->next;
				War->next = newNode;
			}
			else {
				War = newNode;
				Horror->next = War;
			}
			War = newNode;
		}

		else if (genre == "Biography") {

			if (Biography != NULL) {
				newNode->next = Biography->next;
				Biography->next = newNode;
			}
			else {
				Biography = newNode;
				War->next = Biography;
			}
			Biography = newNode;
		}

		else if (genre == "Music") {

			if (Music != NULL) {
				newNode->next = Music->next;
				Music->next = newNode;
			}
			else {
				Music = newNode;
				Biography->next = Music;
			}
			Music = newNode;
		}

		else if (genre == "Game-Show") {

			if (Game_Show != NULL) {
				newNode->next = Game_Show->next;
				Game_Show->next = newNode;
			}
			else {
				Game_Show = newNode;
				Music->next = Game_Show;
			}
			Game_Show = newNode;
		}

		else if (genre == "Reality-TV") {

			if (Reality_TV != NULL) {
				newNode->next = Reality_TV->next;
				Reality_TV->next = newNode;
			}
			else {
				Reality_TV = newNode;
				Game_Show->next = Reality_TV;
			}
			Reality_TV = newNode;
		}

		else if (genre == "News") {

			if (News != NULL) {
				newNode->next = News->next;
				News->next = newNode;
			}
			else {
				News = newNode;
				Reality_TV->next = News;
			}
			News = newNode;
		}

		else if (genre == "Short") {

			if (Short != NULL) {
				newNode->next = Short->next;
				Short->next = newNode;
			}
			else {
				Short = newNode;
				News->next = Short;
			}
			Short = newNode;
		}

		else if (genre == "Film-Noir") {

			if (Film_Noir != NULL) {
				newNode->next = Film_Noir->next;
				Film_Noir->next = newNode;
			}
			else {
				Film_Noir = newNode;
				Short->next = Film_Noir;
			}
			Film_Noir = newNode;
			Film_Noir->next = NULL;
		}


	}//End of method InsertByGenre.


	/*Static method. Also used in DirectorList class' method GetDirectorsOfGenre.
	* Locates the position of a genre in the IndexedByGenre list.
	* Specifies the location in temp and tempPrev.
	* Worst case time complexity is O(1) i.e constant.
	* Best case complexity is also the same.
	*/
	static Node<Movie*>* LocateGenre(string genre, IndexedByGenre* moviesByGenre, Node<Movie*>** tempPrev) {

		Node<Movie*>* temp = NULL;

		if (genre == "Action") {
			temp = moviesByGenre->Action;
			*(tempPrev) = moviesByGenre->start;
		}
		else if (genre == "Adventure") {
			temp = moviesByGenre->Adventure;
			*(tempPrev) = moviesByGenre->Action;
		}

		else if (genre == "Fantasy") {
			temp = moviesByGenre->Fantasy;
			*(tempPrev) = moviesByGenre->Adventure;
		}

		else if (genre == "Sci-Fi") {
			temp = moviesByGenre->Sci_Fi;
			*(tempPrev) = moviesByGenre->Fantasy;
		}

		else if (genre == "Thriller") {
			temp = moviesByGenre->Thriller;
			*(tempPrev) = moviesByGenre->Sci_Fi;
		}

		else if (genre == "Documentary") {
			temp = moviesByGenre->Documentary;
			*(tempPrev) = moviesByGenre->Thriller;
		}

		else if (genre == "Romance") {
			temp = moviesByGenre->Romance;
			*(tempPrev) = moviesByGenre->Documentary;
		}

		else if (genre == "Animation") {
			temp = moviesByGenre->Animation;
			*(tempPrev) = moviesByGenre->Romance;
		}
		else if (genre == "Comedy") {
			temp = moviesByGenre->Comedy;
			*(tempPrev) = moviesByGenre->Animation;
		}

		else if (genre == "Family") {
			temp = moviesByGenre->Family;
			*(tempPrev) = moviesByGenre->Comedy;
		}

		else if (genre == "Musical") {
			temp = moviesByGenre->Musical;
			*(tempPrev) = moviesByGenre->Family;
		}

		else if (genre == "Mystery") {
			temp = moviesByGenre->Mystery;
			*(tempPrev) = moviesByGenre->Musical;
		}

		else if (genre == "Western") {
			temp = moviesByGenre->Western;
			*(tempPrev) = moviesByGenre->Mystery;
		}

		else if (genre == "Drama") {
			temp = moviesByGenre->Drama;
			*(tempPrev) = moviesByGenre->Western;
		}

		else if (genre == "History") {
			temp = moviesByGenre->History;
			*(tempPrev) = moviesByGenre->Drama;
		}

		else if (genre == "Sport") {
			temp = moviesByGenre->Sport;
			*(tempPrev) = moviesByGenre->History;
		}

		else if (genre == "Crime") {
			temp = moviesByGenre->Crime;
			*(tempPrev) = moviesByGenre->Sport;
		}

		else if (genre == "Horror") {
			temp = moviesByGenre->Horror;
			*(tempPrev) = moviesByGenre->Crime;
		}

		else if (genre == "War") {
			temp = moviesByGenre->War;
			*(tempPrev) = moviesByGenre->Horror;
		}

		else if (genre == "Biography") {
			temp = moviesByGenre->Biography;
			*(tempPrev) = moviesByGenre->War;
		}

		else if (genre == "Music") {
			temp = moviesByGenre->Music;
			*(tempPrev) = moviesByGenre->Biography;
		}

		else if (genre == "Game-Show") {
			temp = moviesByGenre->Game_Show;
			*(tempPrev) = moviesByGenre->Music;
		}

		else if (genre == "Reality-TV") {
			temp = moviesByGenre->Reality_TV;
			*(tempPrev) = moviesByGenre->Game_Show;
		}

		else if (genre == "News") {
			temp = moviesByGenre->News;
			*(tempPrev) = moviesByGenre->Reality_TV;
		}

		else if (genre == "Short") {
			temp = moviesByGenre->Short;
			*(tempPrev) = moviesByGenre->News;
		}

		else if (genre == "Film-Noir") {
			temp = moviesByGenre->Film_Noir;
			*(tempPrev) = moviesByGenre->Short;
		}
		else {
			cout << "\nIncorrect genre." << endl;
			*(tempPrev) = NULL;
		}

		return temp;

	}//End of method.


	/*Displays all movies of specified genre rating-wise.
	* Takes the genre as argument.
	* Uses a local IndexedMovieList to store all the movies of specified genre rating-wise.
	* Worst case time complexity is O(n) where n = No. of movies of specified genre. Not counting the
	 searching operation used for inserting movies in IndexedMovieList.
	* Best case complexity is also the same.
	*/
	void PrintByGenreRatingWise(string genre) {

		Node<Movie*>* tempPrev = start;
		Node<Movie*>* temp = LocateGenre(genre, this, &tempPrev);

		if (temp == NULL) {
			cout << "No movies found of this genre\n";
			return;
		}

		if (tempPrev != start)
			tempPrev = tempPrev->next;

		//Creating a local indexed by rating list to store movies of specified genre rating-wise.
		IndexedMovieList moviesByRating;

		//Storing all movies of specified genre rating-wise in moviesByRating list.
		while (tempPrev != temp->next) {
			moviesByRating.indexedByRating->InsertByYearOrRating(tempPrev->data, "rating");
			tempPrev = tempPrev->next;
		}

		//Diplaying the movies of specified genre rating-wise in increasing order.
		//To print in decreasing order, simply specify "decreasing" as second argument.
		moviesByRating.PrintByRating(moviesByRating.indexedByRating->start);

		//Destroying the locally created list.
		moviesByRating.DestroyList();

	}//End of method PrintByGenre.


};//End of class IndexedByGenre.



/*Singly linked list for actors.
* dtype can be Actor for a list of ActorNodes with Actors in data part.
* or Actor* for a list of ActorNodes with pointer to Actors in data part.
*/
template <typename dtype>
class ActorList {
public:
	Node<dtype>* start;
	Node<dtype>* last;
	Node<dtype>* loc;
	Node<dtype>* pLoc;

	Actor* lastActorInserted;

	//Constructor.
	ActorList() {
		start = NULL;
		last = NULL;
		loc = NULL;
		pLoc = NULL;

		lastActorInserted = NULL;
	}

	bool IsEmpty() {
		return start == NULL;
	}

	/*To search the logical position of an actor by name.
	* Takes the actor name to be searched as argument and modifies
	* loc and pLoc accordingly.
	* pLoc = NULL implies position should be at start.
	* pLoc = Last imples position should be at last.
	* loc = start imples value found at head node.
	* loc = last imples calue found at last node.
	* loc = NULL implies value not found but pLoc suggests logical position.
	* Worst case time complexity is O(n).
	* Best case complexity is constant.
	*/
	void SearchByName(string name) {
		//loc may not be start and pLoc may not be NULL.
		loc = start;
		pLoc = NULL;

		if (IsEmpty())
			return;

		while (loc != NULL && loc->data.name < name) {
			pLoc = loc;
			loc = loc->next;
		}

		//If loc is not NULL and value is not found.
		if (loc != NULL && loc->data.name != name)
			loc = NULL;

	}//End of method SearchByName.


	/*To insert an actor at its logical position by name.
	* Takes an actor as argumentand inserts it at it's logical position.
	* Assuming ascending order A - Z;
	* Worst case time complexity is O(1) not counting the search operation.
	* Best case complexity is also the same.
	*/
	void InsertByName(Actor actor) {

		SearchByName(actor.name);

		//If actor is already in the list.
		if (loc != NULL)
			return;

		Node<Actor>* newNode = new Node<Actor>();
		newNode->data = actor;

		//If actor is not in list.
		if (pLoc == NULL) {//Position should be at start.
			if (IsEmpty())
				last = newNode;
			else
				newNode->next = start;

			start = newNode;
		}

		else if (pLoc == last) {//Position should be at last.
			last->next = newNode;
			last = newNode;
		}
		else {//Position is in-between.
			newNode->next = pLoc->next;
			pLoc->next = newNode;
		}

		lastActorInserted = &(newNode->data);

	}//End of method InsertByName.


	/*To insert at end. For ActorLists of ActorNodes
	* which have pointer to Actors in data part.
	* Takes the address of an actor and appends at the end
	* of the ActorList<Actor *>
	* Worst case time complexity is O(1).
	* Best case complexity is also the same.
	*/
	void Append(Actor* actor) {

		Node<Actor*>* newNode = new Node<Actor*>();
		newNode->data = actor;

		if (IsEmpty())
			start = newNode;
		else
			last->next = newNode;

		last = newNode;

	}//End of method Append.


	/**********************Required Operations Implementations**********************/

	/*To search the profile of an actor.
	* Takes name of the actor as input.
	* If found, prints the name of the actor,
	* movies acted in chronological order with year
	* and there count.
	* Worst case time complexity is O(n) where n = No. of movies this actor acted in.
	  Not counting the search operation.
	* Best case complexity is also the same.
	*/
	void SearchProfile(string actorName) {

		SearchByName(actorName);

		//If not found return.
		if (loc == NULL) {
			cout << "Actor not found" << endl;
			return;
		}


		cout << "\nName: " << loc->data.name << endl;

		Node<Movie*>* temp = loc->data.moviesActedIn->start;

		cout << "\nMovies are:\n\n";
		int count = 0;//To count number of movies this actor acted in.

		while (temp != NULL) {
			cout << temp->data->title << " | " << temp->data->title_year << endl;
			temp = temp->next;
			count++;
		}

		cout << "\nTotal movies are: " << count << endl;

	}//End of method SearchProfile.


	/*To search coacters of an actor.
	* Takes name of the actor as input.
	* Prints all co-acters of an actor with movie titles.
	* A coacter is printed as many times as it is found.
	* Worst case time complexity is O(n) where n = No. of movies this actor acted in.
	  Not counting the search operation.
	* Best case complexity is also the same.
	*/
	void SearchCoacters(string actorName) {

		//Searching location of the actor.
		SearchByName(actorName);

		//If actor is found, then its address is in loc. Else loc is NULL.
		if (loc == NULL) {
			cout << "Actor not found" << endl;
			return;
		}

		//Storing start of the list of this actor's movies in temp.
		Node<Movie*>* temp = loc->data.moviesActedIn->start;

		//Iterating over all the movies of this actor and printing co-actors.
		while (temp != NULL) {

			//Printing movie title.
			cout << temp->data->title << endl;

			//If this actor is actor 1 then actors 2 and 3 are co-actors.
			if (temp->data->actors->start->data->name == actorName) {
				cout << temp->data->actors->start->next->data->name << " | ";
				cout << temp->data->actors->start->next->next->data->name << endl;
			}

			//If this actor is actor 2 then actors 1 and 3 are co-actors.
			else if (temp->data->actors->start->next->data->name == actorName) {
				cout << temp->data->actors->start->data->name << " | ";
				cout << temp->data->actors->start->next->next->data->name << endl;
			}

			//If this actor is actor 3 then actors 1 and 2 are co-actors.
			else {
				cout << temp->data->actors->start->next->data->name << " | ";
				cout << temp->data->actors->start->data->name << endl;
			}

			cout << "\n";
			//Pointing to the next movie.
			temp = temp->next;

		}//End of while loop.

	}//End of method SearchCoacters.



	/*To search unique co-actors of an actor.
	* Takes the name of an actor as input.
	* Prints all unique co-actors along with movie titles.
	* If the same co-actor is encountered again then it is skipped.
	* Worst case time complexity is O(n) where n = No. of movies this actor acted in.
	  Not counting any of the search operation.
	* Best case complexity is also the same.
	*/
	void SearchUniqueCoactors(string actorName) {

		//Searching location of the actor.
		SearchByName(actorName);

		//If actor is found, then its address is in loc. Else loc is NULL.
		if (loc == NULL) {
			cout << "Actor not found" << endl;
			return;
		}

		//Storing start of the list of this actor's movies in temp.
		Node<Movie*>* temp = loc->data.moviesActedIn->start;

		//Maintaining a local string type linked list to store the names
		//Of unique co-actors.
		UniqueCoactorsList uniqueCoactors;
		bool isUnique = false;//To print the movie title only if one of the co-actors is unique.

		//Iterating over all the movies of this actor and printing co-actors.
		while (temp != NULL) {

			isUnique = false;

			//If this actor is actor 1 then actors 2 and 3 are co-actors.
			if (temp->data->actors->start->data->name == actorName) {

				//Checking if actor 2 has been displayed or not. (No if loc is NULL)
				uniqueCoactors.SearchByName(temp->data->actors->start->next->data->name);

				//If actor 2 is unique.
				if (uniqueCoactors.loc == NULL) {
					uniqueCoactors.InsertSorted(temp->data->actors->start->next->data->name);
					cout << temp->data->actors->start->next->data->name << " | ";
					isUnique = true;
				}

				//Checking if actor 3 has been displayed or not. (No if loc is NULL)
				uniqueCoactors.SearchByName(temp->data->actors->start->next->next->data->name);

				//If actor 3 is unique.
				if (uniqueCoactors.loc == NULL) {
					uniqueCoactors.InsertSorted(temp->data->actors->start->next->next->data->name);
					cout << temp->data->actors->start->next->next->data->name << " | ";
					isUnique = true;
				}

				//Displaying movie title if atleast one co-actor is unique.
				if (isUnique)
					cout << "\nMovie: " << temp->data->title << "\n" << endl;

			}



			//If this actor is actor 2 then actors 1 and 3 are co-actors.
			else if (temp->data->actors->start->next->data->name == actorName) {

				//Checking if actor 1 has been displayed or not. (No loc is NULL)
				uniqueCoactors.SearchByName(temp->data->actors->start->data->name);

				//If actor 1 is unique.
				if (uniqueCoactors.loc == NULL) {
					uniqueCoactors.InsertSorted(temp->data->actors->start->data->name);
					cout << temp->data->actors->start->data->name << " | ";
					isUnique = true;
				}

				//Checking if actor 3 has been displayed or not. (No loc is NULL)
				uniqueCoactors.SearchByName(temp->data->actors->start->next->next->data->name);

				//If actor 3 is unique.
				if (uniqueCoactors.loc == NULL) {
					uniqueCoactors.InsertSorted(temp->data->actors->start->next->next->data->name);
					cout << temp->data->actors->start->next->next->data->name << " | ";
					isUnique = true;
				}

				//Displaying movie title if atleast one co-actor is unique.
				if (isUnique)
					cout << "\nMovie: " << temp->data->title << "\n" << endl;

			}



			//If this actor is actor 3 then actors 1 and 2 are co-actors.
			else {

				//Checking if actor 1 has been displayed or not. (No loc is NULL)
				uniqueCoactors.SearchByName(temp->data->actors->start->data->name);

				//If actor 1 is unique.
				if (uniqueCoactors.loc == NULL) {
					uniqueCoactors.InsertSorted(temp->data->actors->start->data->name);
					cout << temp->data->actors->start->data->name << " | ";
					isUnique = true;
				}

				//Checking if actor 2 has been displayed or not. (No loc is NULL)
				uniqueCoactors.SearchByName(temp->data->actors->start->next->data->name);

				//If actor 2 is unique.
				if (uniqueCoactors.loc == NULL) {
					uniqueCoactors.InsertSorted(temp->data->actors->start->next->data->name);
					cout << temp->data->actors->start->next->data->name << " | ";
					isUnique = true;
				}

				//Displaying movie title if atleast one co-actor is unique.
				if (isUnique)
					cout << "\nMovie: " << temp->data->title << "\n" << endl;

			}

			//Pointing to the next movie.
			temp = temp->next;

		}//End of while loop.

		//Destroying this local list.
		uniqueCoactors.DestroyList();

	}//End of method SearchUniqueCoactors.



	/*To search for all co-actors of all co-actors of an actor.
	* Takes the name of an actor as input.
	* Prints all unique co-actors of all co-actors with movie titles.
	* If a co-actor
	* Worst case time complexity is O(a * b)
	  where a = No. of movies this actor acted in.
			b = No. of movies of co-actors
	  'a' beacuase a loop iterates over all movies of this actor.
	  'b' beacuse for each iteration of a, a loop iterates over all co-actors of a co-actor.		
	  Not counting the search operation.
	* Best case complexity is also the same.
	*/
	void SearchCoactorsOfCoactors(string actorName) {

		//Searching location of the actor.
		SearchByName(actorName);

		//If actor is found, then its address is in loc. Else loc is NULL.
		if (loc == NULL) {
			cout << "Actor not found" << endl;
			return;
		}

		//Storing start of the list of this actor's movies in temp.
		Node<Movie*>* temp = loc->data.moviesActedIn->start;

		//Maintaining a local string type linked list to store the names
		//Of unique co-actors of the searched actor..
		UniqueCoactorsList uniqueCoactors;
		//bool isUnique = false;//To display the co=actors of only the unique co-actors of the searched actor.

		//Iterating over all the movies of this actor.
		while (temp != NULL) {

			//If this actor is actor 1 then actors 2 and 3 are co-actors.
			if (temp->data->actors->start->data->name == actorName) {

				//Checking of 2 is unique.
				uniqueCoactors.SearchByName(temp->data->actors->start->next->data->name);

				//Displaying co-actors of this co-actor if they have not yet been displayed.
				//And storing its name.
				if (uniqueCoactors.loc == NULL) {
					cout << "Co-actor: " << temp->data->actors->start->next->data->name << endl;
					SearchUniqueCoactors(temp->data->actors->start->next->data->name);
					uniqueCoactors.InsertSorted(temp->data->actors->start->next->data->name);
				}

				//Checking if 3 is unique.
				uniqueCoactors.SearchByName(temp->data->actors->start->next->next->data->name);

				//Displaying co-actors of this co-actor if they have not yet been displayed.
				//And storing its name.
				if (uniqueCoactors.loc == NULL) {
					cout << "Co-actor: " << temp->data->actors->start->next->next->data->name << endl;
					SearchUniqueCoactors(temp->data->actors->start->next->next->data->name);
					uniqueCoactors.InsertSorted(temp->data->actors->start->next->next->data->name);
				}


			}



			//If this actor is actor 2 then actors 1 and 3 are co-actors.
			else if (temp->data->actors->start->next->data->name == actorName) {

				//Checking of 1 is unique.
				uniqueCoactors.SearchByName(temp->data->actors->start->data->name);

				//Displaying co-actors of this co-actor if they have not yet been displayed.
				//And storing its name.
				if (uniqueCoactors.loc == NULL) {
					cout << "Co-actor: " << temp->data->actors->start->data->name << endl;
					SearchUniqueCoactors(temp->data->actors->start->data->name);
					uniqueCoactors.InsertSorted(temp->data->actors->start->data->name);
				}

				//Checking of 3 is unique.
				uniqueCoactors.SearchByName(temp->data->actors->start->next->next->data->name);

				//Displaying co-actors of this co-actor if they have not yet been displayed.
				//And storing its name.
				if (uniqueCoactors.loc == NULL) {
					cout << "Co-actor: " << temp->data->actors->start->next->next->data->name << endl;
					SearchUniqueCoactors(temp->data->actors->start->next->next->data->name);
					uniqueCoactors.InsertSorted(temp->data->actors->start->next->next->data->name);
				}


			}



			//If this actor is actor 3 then actors 1 and 2 are co-actors.
			else {

				//Checking of 1 is unique.
				uniqueCoactors.SearchByName(temp->data->actors->start->data->name);

				//Displaying co-actors of this co-actor if they have not yet been displayed.
				//And storing its name.
				if (uniqueCoactors.loc == NULL) {
					cout << "Co-actor: " << temp->data->actors->start->data->name << endl;
					SearchUniqueCoactors(temp->data->actors->start->data->name);
					uniqueCoactors.InsertSorted(temp->data->actors->start->data->name);
				}

				//Checking of 2 is unique.
				uniqueCoactors.SearchByName(temp->data->actors->start->next->data->name);

				//Displaying co-actors of this co-actor if they have not yet been displayed.
				//And storing its name.
				if (uniqueCoactors.loc == NULL) {
					cout << "Co-actor: " << temp->data->actors->start->next->data->name << endl;
					SearchUniqueCoactors(temp->data->actors->start->next->data->name);
					uniqueCoactors.InsertSorted(temp->data->actors->start->next->data->name);
				}

			}


			//Pointing to the next movie.
			temp = temp->next;


		}//End of while loop.


		//Destroying this local list.
		uniqueCoactors.DestroyList();

	}//End of method SearchCoactorsOfCoactors.


	/*To search if two given actors are co-actors or not.
	* Takes the names of the two actors as input.
	* If both have worked together in one or more movies, prints there titles.
	* If same names are entered returns.
	* Worst case time complexity is O(n) where n = No. of movies of actor 1. Not counting the search operations.
	* Best case complexity is also the same.
	*/
	void CheckIfCoactors(string actor1, string actor2) {

		if (actor1 == actor2) {
			cout << "The two names entered refer to the same actor." << endl;
			return;
		}

		//Searching location of actor 2.
		SearchByName(actor2);
		if (loc == NULL) {
			cout << "Actor 2 not found" << endl;
			return;
		}
		//Searching location of actor 1.
		SearchByName(actor1);
		if (loc == NULL) {
			cout << "Actor 1 not found" << endl;
			return;
		}

		//Storing start of movies list of actor 1 in temp.
		Node<Movie*>* temp = loc->data.moviesActedIn->start;
		bool areCoactors = false;

		cout << "Movies are:\n";
		//Iterating over all the movies of actor 1 to check its co-actors.
		while (temp != NULL) {

			if (temp->data->actors->start->data->name == actor2) {
				cout << temp->data->title << endl;
				areCoactors = true;
			}

			else if (temp->data->actors->start->next->data->name == actor2) {
				cout << temp->data->title << endl;
				areCoactors = true;
			}

			else if (temp->data->actors->start->next->data->name == actor2) {
				cout << temp->data->title << endl;
				areCoactors = true;
			}

			temp = temp->next;

		}//End of while loop.

		if (!areCoactors)
			cout << "None\n" << actor1 << " and " << actor2 << " have not acted together." << endl;

	}//End of method CheckIfCoactors.



};//End of class ActorList.



/*Singly linked list for directors.
* dtype can be Dirctor for a list of DirctorNodes with Dirctors in data part.
* or Dirctor* for a list of DirctorNodes with pointer to Dirctors in data part.
*/
template <typename dtype>
class DirectorList {
public:
	Node<dtype>* start;
	Node<dtype>* last;
	Node<dtype>* loc;
	Node<dtype>* pLoc;
	Director* lastDirectorInserted;

	//Constructor.
	DirectorList() {
		start = NULL;
		last = NULL;
		loc = NULL;
		pLoc = NULL;

		lastDirectorInserted = NULL;
	}

	bool IsEmpty() {
		return start == NULL;
	}

	/*To search the logical position of a director by name.
	* Takes the director name to be searched as argumentand modifies
	* locand pLoc accordingly.
	* pLoc = NULL implies position should be at start.
	* pLoc = Last imples position should be at last.
	* loc = start imples value found at head node.
	* loc = last imples calue found at last node.
	* loc = NULL implies value not found but pLoc suggests logical position.
	* Worst case time complexity is O(n).
	* Best case complexity is constant.
	*/
	void SearchByName(string name) {

		//loc may not be start and pLoc may no be NULL.
		loc = start;
		pLoc = NULL;

		if (IsEmpty())
			return;

		while (loc != NULL && loc->data.name < name) {
			pLoc = loc;
			loc = loc->next;
		}

		//If loc is not NULL and value is not found.
		if (loc != NULL && loc->data.name != name)
			loc = NULL;

	}//End of method SearchByName;


	/*TO insert a director at its logical position by name.
	* Takes an director as argumentand inserts it at it's logical position.
	* Assuming ascending order A - Z;
	* Worst case time complexity is O(1). Not counting the search operation.
	* Best case complexity is also constant.
	*/
	void InsertByName(Director director) {

		SearchByName(director.name);

		//If actor is already in the list.
		if (loc != NULL)
			return;

		Node<Director>* newNode = new Node<Director>();
		newNode->data = director;

		//If actor is not in list.
		if (pLoc == NULL) {//Position should be at start.
			if (IsEmpty())
				last = newNode;
			else
				newNode->next = start;

			start = newNode;
		}

		else if (pLoc == last) {//Position should be at last.
			last->next = newNode;
			last = newNode;
		}
		else {//Position is in-between.
			newNode->next = pLoc->next;
			pLoc->next = newNode;
		}

		lastDirectorInserted = &(newNode->data);

	}//End of method InsertByName.


	/*To insert at end. For DirectorLists of DirectorNodes
	* which have pointer to Directors in data part.
	* Takes the address of an Director and appends at the end
	* of the DirectorList<Director *>
	* Worst case time complexity is O(1).
	* Best case complexity is also constant.
	*/
	void Append(Director* director) {

		Node<Director*>* newNode = new Node<Director*>();
		newNode->data = director;

		if (IsEmpty())
			start = newNode;
		else
			last->next = newNode;

		last = newNode;

	}//End of method Append.


	/**********************Required Operations Implementations**********************/


	/*To search profile of a director.
	* Takes the name of the director as input.
	* Displays all the movies directed along with their years.
	* Worst case time complexity is O(n) where n = No. of movies directed by the specified director.
	  Not counting the search operation.
	* Best case complexity is also the same.
	*/
	void SearchDirector(string directorName) {

		SearchByName(directorName);

		//If not found return.
		if (loc == NULL) {
			cout << "Director not found." << endl;
			return;
		}

		cout << "Name: " << loc->data.name << endl;

		Node<Movie*>* temp = loc->data.MoviesDirected->start;

		cout << "Movies: " << endl;

		//Iterating over all movies directed.
		while (temp != NULL) {

			cout << temp->data->title << " | " << temp->data->title_year << endl;
			temp = temp->next;
		}

	}//End of method SearchDirector.


	/*To print all directors who have directed movies of a given genre.
	* Takes name of the genre and start pointer of moviesByGenre.
	* Uses the above function (LocateGenre) to locate the position of movies
	  of this genre in IndexedByGenre list.
	* Worst case time Complexity O(n) where n = No. of movies of the specified genre.
	* Best case complexity is also the same.
	*/
	void GetDirectorsOfGenre(string genre, IndexedByGenre* moviesByGenre) {


		Node<Movie*>* tempPrev = moviesByGenre->start;
		Node<Movie*>* temp = IndexedByGenre::LocateGenre(genre, moviesByGenre, &tempPrev);

		if (tempPrev == NULL) {
			return;
		}

		if (tempPrev != moviesByGenre->start)
			tempPrev = tempPrev->next;

		//Iterating over all movies of the specified genre.
		while (tempPrev != temp->next) {

			cout << tempPrev->data->director->name << endl;
			tempPrev = tempPrev->next;
		}

	}//End of method GetDirectorsOfGenre.


};//End of class DirectorList.



//Singly linked list for storing Genres of a Movie.
class GenreList {
public:
	Node<string>* start;
	Node<string>* last;

	//Default constructor.
	GenreList() {
		start = NULL;
		last = NULL;
	}

	bool IsEmpty() {
		return start == NULL;
	}

	/*Appends the value at the end of the list.
	* Worst case time complexity is O(1).
	* Best case complexity is also constant.
	*/
	void Append(string value) {

		Node<string>* newNode = new Node<string>();
		newNode->data = value;

		if (IsEmpty())
			start = newNode;
		else
			last->next = newNode;

		last = newNode;

	}//End of method Append.


	/*This method extracts the genres of a Movie.
	* Worst case time complexity is O(n) where n = No. of genres of the specified movie.
	* Best case complexity is also the same.
	*/
	void SetGenres(string genres, Movie* pmovie) {

		stringstream stream;

		//Associating given genres of a movie with a stream.
		stream << genres;
		//Using the same variable after clearing it.
		genres.clear();

		while (getline(stream, genres, '|')) {
			pmovie->genre->Append(genres);
		}

	}//End of method setGenres.


	/*Prints the genres of the associated movie.
	* Worst case time complexity is O(n) where n = No. of genres of the associated movie.
	* Best case complexity is also the same.
	*/
	void PrintList() {

		if (IsEmpty())
			return;

		Node<string>* temp = start;

		while (temp != NULL) {
			cout << temp->data << "  ";
			temp = temp->next;
		}

	}//End of method PrintList.

};//End of class GenreList.


//Singly linked list for storing Plot keywords of a Movie.
class PlotKeywordsList {
public:
	Node<string>* start;
	Node<string>* last;

	//Default constructor.
	PlotKeywordsList() {
		start = NULL;
		last = NULL;
	}

	bool IsEmpty() {
		return start == NULL;
	}


	/*This method appends the value at the end of the list.
	* Worst case time complexity is O(1)
	* Best case comlexity is also the same.
	*/
	void Append(string value) {

		Node<string>* newNode = new Node<string>();
		newNode->data = value;

		if (IsEmpty())
			start = newNode;
		else
			last->next = newNode;

		last = newNode;

	}//End of method Append.


	/*This method extracts the genres of a Movie.
	* Worst case time complexity is O(n) where n = No. of plot keywords of the specified movie.
	* Best case comlexity is also the same.
	*/
	void SetPlotKeywords(string plotKeywords, Movie* movie) {

		stringstream stream;

		//Associating given plot keywords of a movie with a stream.
		stream << plotKeywords;
		//Using the same variable after clearing it.
		plotKeywords.clear();

		//While there are plot keywords in the stream.
		while (getline(stream, plotKeywords, '|')) {
			movie->plot_keywords->Append(plotKeywords);
		}

	}//End of method SetPlotKeywords.

	/*Prints the plot keywords of the associated movie.
	* Worst case time complexity is O(n) where n = No. of plot keywords of the specified movie.
	* Best case comlexity is also the same.
	*/
	void PrintList() {

		if (IsEmpty())
			return;

		Node<string>* temp = start;
		while (temp != NULL) {
			cout << temp->data << "  ";
			temp = temp->next;
		}

	}

};//End of class PlotKeywordsList



/********************************End of main classes**********************************/

int main() {

	MovieList<Movie>* movieList = new MovieList<Movie>();
	ActorList<Actor>* actorList = new ActorList<Actor>();
	IndexedMovieList* moviesByYear = new IndexedMovieList();
	IndexedMovieList* moviesByRating = new IndexedMovieList();
	DirectorList<Director>* directorList = new DirectorList<Director>();

	IndexedByGenre* moviesByGenre = new IndexedByGenre();

	//Calling extractData to extract all the data (65 movies specified in the loop).
	extractData(movieList, actorList, directorList, moviesByYear, moviesByRating, moviesByGenre);


	/*--------------------------------------------------------------
	 * Note: A '0' in output of a field that is not supposed to be *
	 * '0' indicates that the filed is NULL (empty) in the file    *
	---------------------------------------------------------------*/


	/*****************************Operations related to Actors*****************************/

	string input1;
	string input2;

	//Operation 1. Argument is an actor name.
	cout << "Search an Actor. Input Actor name: ";
	getline(cin, input1);
	cout << endl << endl;
	actorList->SearchProfile(input1);

	//Operation 2. Argument is an actor name.
	cout << "\n\nFind co-actors of an actor. Input name: ";
	getline(cin, input1);
	cout << endl << endl;
	actorList->SearchCoacters(input1);

	//Operation 3. Argument is an actor name.
	cout << "\n\nFind unique co-actors of an actor. Input name: ";
	getline(cin, input1);
	cout << endl << endl;
	actorList->SearchUniqueCoactors(input1);

	//Operation 4. Argument is an actor name.
	cout << "\n\nFind co-actors of co-actors of an actor. Input name: ";
	getline(cin, input1);
	cout << endl << endl;
	actorList->SearchCoactorsOfCoactors(input1);

	//Operation 5. Arguemnt is two actor names.
	//cout << "Checking if Johnny Depp and Orlando Bloom have acted together\n";
	cout << "\n\nCheck if two actors have worked together. Input names: \n";
	getline(cin, input1);
	getline(cin, input2);
	cout << endl << endl;
	actorList->CheckIfCoactors(input1, input2);


	/*****************************Operations related to Directors*****************************/

	//Operation 6. Argument is a name of a director.
	cout << "\n\nSearch a director. Input name: ";
	getline(cin, input1);
	cout << endl << endl;
	directorList->SearchDirector(input1);

	//Operation 7. Argument is a genre e.g "Adventure" etc.
	cout << "\n\nFind directors who have directed movies of genre: ";
	getline(cin, input1);
	cout << endl << endl;
	directorList->GetDirectorsOfGenre(input1, moviesByGenre);


	/*****************************Operations related to Movies*****************************/

	//Operation 8. Argument is a title of a movie.
	cout << "\n\nFind a movie. Input complete title: ";
	getline(cin, input1);
	cout << endl << endl;
	movieList->FindMovie(input1);	

	//Operation 9. Argument is a year e.g 2009 etc.
	cout << "\n\nFind all movies in year: ";
	getline(cin, input1);
	cout << endl << endl;
	moviesByYear->FindMoviesInYear(stoi(input1));


	//Operation 10. Specify order in 2nd argument e.g "decreasing"
	cout << "\n\nAll movies sorted by year. Order (increasing or decreasing)?: \n" << endl;
	getline(cin, input1);
	cout << endl << endl;
	moviesByYear->PrintByYear(moviesByYear->indexedByYear->start, input1);

	//Operation 11. Specify order in 2nd argument e.g "decreasing"
	cout << "\n\nAll movies sorted by rating (imdb_score) Order (increasing or decreasing)?: \n" << endl;
	getline(cin, input1);
	cout << endl << endl;
	moviesByRating->PrintByRating(moviesByRating->indexedByRating->start, input1);

	//Operation 12 . Argument is a genre e.g "Adventure" etc.
	cout << "\n\nAll movies sorted by genre rating-wise in increasing order. Genre?: \n" << endl;
	getline(cin, input1);
	cout << endl << endl;
	moviesByGenre->PrintByGenreRatingWise(input1);

	cout << "\n\n**Thank You :)**" << endl << endl;

	//cout <<"\n\All movies sorted by title: \n" << endl;
	//movieList->PrintList();

	return 0;
}



/*This method returns a vector of comma seperated values of a line of a csv file.
* Worst case time complexity is O(1).
* Best case complexity is also the same.
*/
vector<string> parseCsvFile(fstream& file) {

	vector<string> vector;
	stringstream stream;
	string line;
	string word;
	string title;
	

	getline(file, line);
	//Associating line with stringstream object stream.
	stream << line;

	//Extracting title and removing double quotes if any.
	getline(stream, title, 'Â');
	if( title[0] == '"' )
		title.erase(0, 1);

	vector.push_back(title);

	//Extracting comma separated fields.
	for (int i = 0; i < 28;i++) {
		getline(stream, word, ',');

		if (word.empty()) {
			//Setting all empty attributes to 0.
			word = "0";
		}
		vector.push_back(word);

	}

	return vector;
}//End of method parseCsvFile.


/*This method extracts all the data from the dataset into the data structures.
* Worst case time complexity is O(n*m). Where n = No. of movies.
  m = No. of genres of a given movie (a loop is used to index each movie by all its genres).
* Best case complexity is also the same.
*/
void extractData(MovieList<Movie>* movieList, ActorList<Actor>* actorList, DirectorList<Director>* directorList
	, IndexedMovieList* moviesByYear, IndexedMovieList* moviesByRating, IndexedByGenre* moviesByGenre) {

	fstream file;
	string discard;
	vector<string> vector;

	//Opening IMDB_Top5000-SEECS.csv.
	file.open("IMDB_Top5000-SEECS.csv", ios::in);

	//file.open("c:\\Users\\pc\\Downloads\\Semester 3\\DSA\\Midterm Project\\IMDB_Top5000-SEECS.csv", ios::in);

	//Discarding column names (1st line).
	getline(file, discard);


	for (int i = 0;i < NumMovies;i++) {

		//Parsing a line from the file.
		vector = parseCsvFile(file);

		try {

			//Storing data of Actors.
			Actor actor1(vector[9], unsigned short int(stoi(vector[10])));
			Actor actor2(vector[11], unsigned short int(stoi(vector[12])));
			Actor actor3(vector[13], unsigned short int(stoi(vector[14])));

			//Storing data of movie.
			Movie movie(vector);

			//Adding movie in the movie list sorted by title in ascending order.
			movieList->InsertByTitle(movie);

			//Initializing and setting Genre List for this movie.
			movieList->lastMovieInserted->genre = new GenreList();
			movieList->lastMovieInserted->genre->SetGenres(vector[2], movieList->lastMovieInserted);

			//Initializing and setting plot keywords List for this movie.
			movieList->lastMovieInserted->plot_keywords = new PlotKeywordsList();
			movieList->lastMovieInserted->plot_keywords->SetPlotKeywords(vector[19], movieList->lastMovieInserted);


			//Initializing Actors List for this movie.
			movieList->lastMovieInserted->actors = new ActorList<Actor*>();

			//Indexing this movie by year.
			moviesByYear->indexedByYear->InsertByYearOrRating(movieList->lastMovieInserted);

			//Indexing this movie by Rating.
			moviesByRating->indexedByRating->InsertByYearOrRating(movieList->lastMovieInserted, "rating");

			//Indexing this movie by all its genres.
			//-------------------------------------------------------------------------

			//Start of the genreList of this movie.
			Node<string>* temp = movieList->lastMovieInserted->genre->start;

			while (temp != NULL) {
				moviesByGenre->InsertByGenre(temp->data, movieList->lastMovieInserted);
				temp = temp->next;
			}

			//-------------------------------------------------------------------------


			//Adding actors in the actor list sorted by name in ascending order.

			/*******************Actor1*******************/

			actorList->InsertByName(actor1);

			//If this actor is not already in the actorList, then loc will be NULL.
			//As InserByName searches the actor first and updates loc and pLoc.
			if (actorList->loc == NULL) {
				//Updating actors of this movie-Adding actor1.
				movieList->lastMovieInserted->actors->Append(actorList->lastActorInserted);

				//Initializing movieActedIn list for this actor
				actorList->lastActorInserted->moviesActedIn = new MovieList<Movie*>();

				//Updating information for this actor.
				actorList->lastActorInserted->moviesActedIn->InsertByYearOrRating(movieList->lastMovieInserted);

			}

			//If this actor is already in the actorList it's Node's address will be in actorList->loc.
			else {
				movieList->lastMovieInserted->actors->Append(&(actorList->loc->data));
				actorList->loc->data.moviesActedIn->InsertByYearOrRating(movieList->lastMovieInserted);
			}

			/*******************Actor2*******************/

			actorList->InsertByName(actor2);

			//If this actor is not already in the actorList.
			if (actorList->loc == NULL) {
				movieList->lastMovieInserted->actors->Append(actorList->lastActorInserted);
				actorList->lastActorInserted->moviesActedIn = new MovieList<Movie*>();
				actorList->lastActorInserted->moviesActedIn->InsertByYearOrRating(movieList->lastMovieInserted);
			}

			//If this actor is already in the actorList it's Node's address will be in actorList->loc.
			else {
				movieList->lastMovieInserted->actors->Append(&(actorList->loc->data));
				actorList->loc->data.moviesActedIn->InsertByYearOrRating(movieList->lastMovieInserted);
				//cout << actorList->loc->data.name << " 2 " << endl;
			}


			/*******************Actor3*******************/

			actorList->InsertByName(actor3);

			//If this actor is not already in the actorList.
			if (actorList->loc == NULL) {
				movieList->lastMovieInserted->actors->Append(actorList->lastActorInserted);
				actorList->lastActorInserted->moviesActedIn = new MovieList<Movie*>();
				actorList->lastActorInserted->moviesActedIn->InsertByYearOrRating(movieList->lastMovieInserted);
			}

			//If this actor is already in the actorList it's Node's address will be in actorList->loc.
			else {
				movieList->lastMovieInserted->actors->Append(&(actorList->loc->data));
				actorList->loc->data.moviesActedIn->InsertByYearOrRating(movieList->lastMovieInserted);
			}


			/*******************Director*******************/

			//Storing data of the Director.
			Director director(vector[5], unsigned short int(stoi(vector[6])));

			//Adding director in the director list sorted by name in ascending order.
			directorList->InsertByName(director);

			//If this director is not already in the directorlist.
			if (directorList->loc == NULL) {

				//Updating director for this movie.
				movieList->lastMovieInserted->director = directorList->lastDirectorInserted;

				//Initializing MoviesDirected list for this director
				directorList->lastDirectorInserted->MoviesDirected = new MovieList<Movie*>();
				directorList->lastDirectorInserted->MoviesDirected->InsertByYearOrRating(movieList->lastMovieInserted);
			}

			//If this director is already in the directorlist then it's node's address will be in loc.
			else {
				movieList->lastMovieInserted->director = &(directorList->loc->data);
				directorList->loc->data.MoviesDirected->InsertByYearOrRating(movieList->lastMovieInserted);
			}


		}//End of try clause.

		catch (invalid_argument ex) {
			cout << ex.what() << endl;
		}


	}//End of for loop.


	file.close();

}//End of method extractData.



