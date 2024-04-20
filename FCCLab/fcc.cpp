#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "fcc.h"

bool more_to_read(std::ifstream &file)
{
  file >> std::noskipws;
  while (file.peek() == ' ')
  {
    char discard;
    file >> discard;
  }
  return !(file.eof() || std::iscntrl(file.peek()));
}

/*1) read input from the fixos and typos file\
	ifstream fixos;\ cehck
	ifstream typos;\ check
2) correlate the lists (what fixos file goes with what typos file)\
	read the contents of the list and see if they are similar\ check
3) make sure that both lists have the same number of entries\\	check the same number of values in the vector lists f[0] == t[0] as a loop\
check
4) read in the sentence to fix\
	ifstream fixme;\ check
5) go through the words in the sentence and determine which one needs to be fixed\
	compare the words and equate them to the fixo file if they are not the same in the typos file\
	}
*/
/*
 * <read_from_file>
 *
 * <short description of what the function does>
 *
 * input: typo file
 * output: reads the words contained in the typo file
 */
std::vector<std::string> read_from_file(std::ifstream & file)
  {
    std::vector<std::string> words;
    while (more_to_read(file))
    {
      std::string next_word;
      file >> next_word;
      words.push_back(next_word);
    }
    return words;
  }

int fcc(const std::string &fixme_filename, const std::string &typo_filename,
        const std::string &fixo_filename, std::string &fixed_sentence)
{

  std::ifstream fixos_file;
  std::ifstream typos_file;
  std::ifstream fixme_file;
  fixme_file.open(fixme_filename);
  fixos_file.open(fixo_filename);
  typos_file.open(typo_filename);


  std::vector<std::string> fixos;
  std::vector<std::string> typos;
  std::vector<std::string> fixme;

  bool arraysEqual = true;
  int count = 0;
  int error_count = 0;
  

  /*
 * read-in
 *
 * reads the files from fixo, typo, and fixme
 *
 * input: fixos_file, typos_file, fixme_file
 * output: read data from the three files
 */
  fixos = read_from_file(fixos_file);
  typos = read_from_file(typos_file);
  fixme = read_from_file(fixme_file);
  if(typos.size() != fixos.size()){
    return -1;
  }
  /*
 * re-naming
 *
 * if the arrays are equal, it will set the vector inncorect spellings
 * to the correct spellings
 *
 * input: size for fixme and typos
 * output: if both are the same size then the typos
 * will be corrected and counts the number of errors
 */

    for (int count = 0; count < fixme.size(); count++){
      for (int count2 = 0; count2 < typos.size(); count2++){
        if (typos[count2] == fixme[count]) {
          fixme[count] = fixos[count2];
          error_count = error_count + 1;
        }
      }
    }
  /*
  * sentance correction
  *
  * takes the incorrectly spelled words
  * and replaces them in the sentance to be spelled correctly
  *
  * input: need_fix string, fixme
  * output: corrected fixme and original sentance
  */
    std::string need_fix{};
    for (int count3 = 0; count3 < fixme.size(); count3++) {
      if (count3 != fixme.size() - 1){ 
        need_fix += fixme[count3] + " ";
      } else{
        need_fix += fixme[count3] + ".";
      }
      
 
    }
    fixed_sentence = need_fix;
    
    
    return error_count;

}


