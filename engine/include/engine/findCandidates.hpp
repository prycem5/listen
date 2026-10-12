#ifndef FINDCANDIDATES_HPP
#define FINDCANDIDATES_HPP
#include <string>
#include <vector>
namespace engine {

/*

    1. normalize(Query query) returns modified query object w/ 
artist (if available) and title cleaned of irrelevant terms (like 
"Official VIdeo", "Official Audio", "Lyrics", etc) as well as converting
strings to lowercase. 

    2. findCandidates(Query query, std::vector<Match> candidates, int k = 3) returns 
list of k candidate matches given normalized query and candidates[]. Candidates are ranked
on duration, title and artist similarity. 

*/

struct Query {
    std::string artist = "none";
    std::string title = "none";
    int duration = 0; // duration in ms.
};

struct Candidate {
    std::string artist = "none";
    std::string title = "none";
    int id = -1; // for mapping back to the typescript object.
    int duration = 0; // duration in ms.
};

struct Match {
    Candidate candidate;
    double score = 0; // computed score, from 0-1,
};


Query normalize(const Query& query);
std::vector<Match> findCandidates(const Query& query, const std::vector<Candidate>& candidates, int k = 3);
}

#endif // FINDCANDIDATES_HPP