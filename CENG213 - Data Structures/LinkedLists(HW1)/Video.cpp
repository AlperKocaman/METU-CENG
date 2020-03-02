#include "Video.hpp"

ostream& operator<<(ostream& out, const Video & video) {
    out << "title:" << video.title << ",genre:" << video.genre << endl;
    return out;
}

/* TO-DO: method implementations below */

Video:: Video() {

	title = "" ;

	genre = "" ;
}
 
Video:: Video(string p_title, string p_genre) {
	
	title = p_title ;

	genre = p_genre ;	
}


Video::~Video() {

}
const string& Video:: getTitle() const {

	return title ;
}

void Video::setTitle(const string& p_title) {

	title = p_title ;
}

const string& Video::getGenre() const {

	return genre ;
}

void Video::setGenre(const string& p_genre) {

	genre = p_genre ;
}

bool Video::operator==(const Video & rhs) const {

	return (title == rhs.getTitle()) ;
}