#include "MediaFactory.h"

std::shared_ptr<Media> MediaFactory::createMedia(const std::string& type, const std::vector<std::string>& args) {
    if (type == "book") {
        if (args.size() != 2) {
            throw std::invalid_argument("Usage: addMedia book <title> <isbn>");
        }
        const std::string& title = args[0];
        const std::string& isbn = args[1];

        if (!Book::isValidISBN(isbn)) {
            throw std::invalid_argument("Invalid ISBN format: " + isbn);
        }
        return std::make_shared<Book>(title, isbn);
    }
    else if (type == "film") {
        if (args.size() != 3) {
            throw std::invalid_argument("Usage: addMedia film <title> <format> <ageLimit>");
        }
        const std::string& title = args[0];
        const std::string& format = args[1];
        int ageLimit = std::stoi(args[2]);

        if (!Film::isValidFormat(format)) {
            throw std::invalid_argument("Invalid film format: " + format + ". Must be Blu-ray or DVD.");
        }
        return std::make_shared<Film>(title, format, ageLimit);
    }
    else if (type == "game") {
        if (args.size() != 4) {
            throw std::invalid_argument("Usage: addMedia game <title> <studio> <genre> <pegi>");
        }
        const std::string& title = args[0];
        const std::string& studio = args[1];
        const std::string& genre = args[2];
        int pegi = std::stoi(args[3]);

        return std::make_shared<Game>(title, studio, genre, pegi);
    }
    else {
        throw std::invalid_argument("Unsupported media type: " + type);
    }
}