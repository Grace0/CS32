
  // Remove the movies in li with a rating below 55 and destroy them.
  // It is acceptable if the order of the remaining movies is not
  // the same as in the original list.
void removeBad(list<Movie*>& li) //li is passed as a reference to a list of pointers to Movies
{
    for (list<Movie*>::iterator it = li.begin(); it != li.end(); ) {
        if ((*it)->rating() < 55) { //dereferencing the iterator will give us a pointer to a Movie
            delete *it; //dereferencing the iterator will give us a pointer to a Movie (which we'll use to delete that Movie)
            it = li.erase(it);
        } else {
            it++;
        }
    }
}

