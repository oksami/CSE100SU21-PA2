# PA2: Multiway Tries and Ternary Search Trees

# Due: Wednesday 7/14/2021, 11:59pm


- [PA2: Multiway Tries and Ternary Search Trees](#pa2-multiway-tries-and-ternary-search-trees)
- [Due: Wednesday 7/14/2021, 11:59pm](#due-wednesday-7142021-1159pm)
- [Overview:](#overview)
- [Retrieving Starter Code](#retrieving-starter-code)
- [Autocompleter](#autocompleter)
  - [Introduction:](#introduction)
  - [Autocompleter](#autocompleter-1)
  - [DictionaryTrie](#dictionarytrie)
    - [Constructor](#constructor)
    - [Insert](#insert)
    - [Find](#find)
    - [Predict Completions](#predict-completions)
    - [Destructor](#destructor)
  - [main in autocomplete.cpp](#main-in-autocompletecpp)
  - [Testing](#testing)
- [Submission Instructions and Grading Breakdown](#submission-instructions-and-grading-breakdown)
  - [Grading](#grading)
  - [Submitting Your PA](#submitting-your-pa)

# Overview: 
In this project, you will be asked to complete text manipulation tasks. You will implement a string autocompleter, like what your browser gives you when you start to type in text. There is also a worksheet for PA2 like what you had for PA1. **Your first step is to _read these instructions carefully._**  We’ve given you a lot of advice here on how to succeed, so please take it.  And please make great use of the search functionality on edstem before you post a question.

# Retrieving Starter Code

The files you retrieve should be the following:

* Makefile (original Makefile)
* DictionaryTrie.hpp
* DictionaryTrie.cpp
* autocomplete.cpp (original file)
* util.cpp (original file)
* util.hpp (original file)

There are also the following useful files in the ~/../public/pa2_refs folder on ieng6. You may choose not to copy the corpuses if you are having issues with quota on your account:

* refautocomplete
* data (folder):
  * freq_dict.txt  
  * unique_freq_dict.txt


In order to compile your code and create the main files, simply run “make” in the terminal inside your pa2 directory.  You can also choose to compile specific executables (try reading the Makefile and see what it does). Our tests compile your code with the make command, so you will need to **make sure that the make command works for the Makefile we give you.**

**NOTE:** SSHing into the server is a thousand times better than setting up locally (if the ieng6 connection is stable), especially if you're working on a Windows machine.

# Autocompleter

## Introduction:
You will write the data structure for a string autocompleter. The idea here is as follows: suppose the user starts typing in a string, let’s say “tho”, then your program's job is to return all the possible words that could possibly complete that string, such as “thought”, “those”, “thoroughly”, and “though”, with **the more probable completions being returned before the less probable ones.** This functionality underlies the autocompletion when you’re texting on your phone, or searching on google. Your autocompleter will learn which completions to return by reading in many words from the real world datasets we’ve provided.

Your assignment is to implement the methods in the DictionaryTrie.hpp file using either a Multiway Trie or Ternary Trie. We have only provided you with the interface you need to implement. You will need to use a Trie to implement this interface.  See the "Autocompleter" section for advice on programming the data structure and additional details on the methods you will implement.

You may use the following parts of the STL:

* vector
* unordered_map (which STL implements as a HashMap/HashTable),
* pair
* The sort method, from `<algorithm>`
* All of the queues and stacks, including priority queue

Outside data structures not listed above are not allowed in this programming assignment. In particular, **you may NOT use std::map**. Using a disallowed data structure qualifies as an academic integrity violation. If you’re not sure, ask. Additionally, you are not required to use the data structures mentioned above; they are only suggestions, and not all good solutions will need them.

Note that we do not provide any tests, so you should write many of your own. This assignment is, in part, designed to challenge you to write a functioning piece of software from end to end, unlike previous assignments (such as the BST) which have given you detailed outlines to work from.

## Autocompleter

Implement the autocompleter using a trie. You may choose to implement either a Ternary Trie or a modified form of the Multiway Trie (explained below). The input to your autocompleter has already been preprocessed (converted to lowercase, stripped of annoying punctuation, split into words or phrases) so you only need to worry about the data structure itself, not the text processing.

In addition, we want to emphasize the fact that **during testing for each PA, there won't be any invalid or meaningless inputs, and you can assume all of the input files and command lines are in correct format.** The focus of the course is data structure and algorithms, and we want you to avoid spending times on trivial details. Don't try to spend time breaking the reference solution or thinking about possible errors coming from the inputs, instead, you should focus on your program itself and spend time on thinking about non-trivial edge cases, assuming no errors coming from inputs.

To generate the completions for a prefix, you’ll find the node in your trie that corresponds to the last letter of the prefix, and look through all of its descendants. You’ll focus on the descendants that are considered words, and amongst those words, choose the ones that occur most frequently.  You will then return the most frequent words in the input text that start with the given prefix. They should be returned in descending order by frequency, meaning that the most frequent words will be first in the returned results.

There are two differences between the trie you need to implement to solve this problem and the tries you’ve seen in class:

1. The first is that this trie must allow for a non-constant range of characters. Most words in the corpus you’ve been provided will not only contain alphabetic characters, but a small percentage will contain numbers, symbols, and spaces among other things (e.g. the word "doesn’t" could be a word in your input). A Ternary Trie can handle this without any modification. However, a traditional Multiway Trie will be memory inefficient. If every node in a traditional Multiway Trie contains an array of pointers of a large fixed size -- if every node contains space for a pointer for each digit just in case that letter in that node is followed by a digit -- you may run out of space or your performance will suffer. If you want to use a Multiway Trie, each node will instead need to use a dynamic array or hash map of pointers to its children, which grows as the node acquires new children. This way, only the nodes which are followed with an apostrophe, for example, have allocated space for a pointer to an apostrophe.

2. The second is that you must store word frequencies in your trie. The simplest way to do this is to, at every word node, store not just an indicator that the node is the end of a word, but also store a count of how many times that word appeared in your training corpus. (**Attention**: you may store more information apart from the frequency, but you are **NOT** allowed to store strings in the node.)

## DictionaryTrie

When writing your Trie data structure, keep in mind that good coding practice dictates that you put different classes you created into separate files (e.g. DictionaryTrie and DictionaryTrieNode, among other possibilities). You should submit all the .cpp and .hpp files from your directory. **One obvious caveat: you have to have written any code included in your turn-in from start to finish.** If you add additional files, you will need to modify the Makefile to compile those files too.  Make sure that your code compiles properly on ieng6. 

You are responsible for implementing the following in DictionaryTrie (implemented either as a Ternary Trie or Multiway Trie):

### Constructor

`DictionaryTrie()`

Initializes a new DictionaryTrie

### Insert

`bool insert(string word, unsigned int freq) `

Insert a word with its frequency into the DictionaryTrie. Return true if the word was inserted, or false if it was not inserted (i.e. the word had already been inserted in the dictionary or the word was invalid (empty string)).

* You can assume a valid freq (i.e. freq > 0).
* If a word has already been inserted, calling insert again with the same word should leave the trie unchanged and return false.

### Find

`bool find(string word) const`

Return true if the word is in the DictionaryTrie and false otherwise.

### Predict Completions

`vector<string> predictCompletions(string prefix, unsigned int num_completions)`

Return a vector holding up to `num_completions` of the most frequent completions of `prefix`, such that the completions are words in the dictionary. These completions should be listed from most to least frequent. If there are fewer than `num_completions` legal completions, this function should return a vector with as many completions as possible. If no completions exist, then the function should return a vector of size 0.  If there are more than one word/phrase with the **same** frequency, they should be ordered **alphabetically**.

Note: The prefix itself may be included in the vector of returned words if the prefix is a word in the DictionaryTrie (and is among the `num_completions` most frequent completions of the pattern).

### Destructor

`~DictionaryTrie()`

Make sure to avoid memory leaks!

## main in autocomplete.cpp

For the autocompleter, you'll need to write a main in `autocomplete.cpp`. This program will take in one file for input. It will read in every word from the file and populate the trie with its corresponding frequencies. Then, it will prompt the user to enter the prefix of a word, as well as the number of suggestions to complete. Then, it will output the most frequent suggestions with that prefix. Note that a prefix itself is a valid completion if it is considered to be a word.

**Hint: You may find the functions in util.hpp to be helpful here**


## Testing

Every step of the way you’ll want to write small tests yourself. If you make a node class, write functions to test all of its methods before moving on. You’ll want to test linking two nodes together before linking a full word together. If you write an insert method on your trie, you’ll want to test inserting a single word before adding many words. Even though you may not use it for autocomplete, you will probably want to implement find and/or print methods on your trie so you know everything’s looking good. And you should test those methods so you know they’re working properly. You’ll want to test corner cases - a word that’s a subset of another word, two words that are nothing alike, etc. In other words, if you can think of it, you should test it. You can model the setup for your test code off of the c++ test code in the BST project.

We have provided dictionary files that you may use to test your implementation. The dictionary files have the following format:

``` shell
 freq_count_1 word_1
 freq_count_2 word_2
 ...
 freq_count_n word_n
```

In `util.cpp`, we have provided a function named `load_dict` that loads the words from the stream with their frequencies into the `DictionaryTrie` object. You can use the method to load words from an open file. It is overloaded to take:

1. Reference to a DictionaryTrie object
2. An istream
3. (optionally) number of words to read in

You can see an example use of this method in `benchtrie.cpp`.

We provided you 2 frequency dictionary files in `~/../public/pa2_refs/data/` for you to test the correctness and performance of your DictionaryTrie. There may be foul language and/or content in the dataset. We neither endorse nor take responsibility for that, but we tried to filter any obvious instances.

In addition to constantly writing tests, you should be constantly backing up your code to GitHub and submitting to Gradescope!

# Submission Instructions and Grading Breakdown

## Grading

The grading for Autocomplete of the project is out of 80 points, and is broken down into 3 categories:

* The code builds properly - if your code does not build and clean properly using your makefile, you will score 0 points.
* 5 points for no memory leak. Memory leaks are notoriously hard to debug if not caught immediately, so test your code frequently, and create checkpoints that you can revert to regularly.
* 24 points for unit tests on various methods.
* 51 points for working correctly and efficiently on a corpus dictionary with random queries.


Lastly, we will be running tests to look for the use of unauthorized libraries or data structures.  In other words, if you try to solve this using code from the web and not build your own (or using disallowed parts of STL), you will receive a zero on the assignment and possibly face an Academic Integrity Violation.

**Be sure to test your code on ieng6.**

**Code which does not compile will not be graded.**

Grading is holistic, and will be mostly black-box tested. This means that we mostly will not test your individual methods, but test your program as a whole. **It is very important that your output matches the output format mentioned in write up or any provided reference executables.**

## Submitting Your PA

You can drag and drop your files or submit your code using Gradescope through Github submission option. You should have gotten enrolled in Gradescope by now (if not, please add your name to the appropriate edstem post). You should also be able to make **private** repositories on Github.

Instructions to submit your code on GradeScope:

1. **Be sure to test your code on ieng6.** We will be grading your code on the same environment as ieng6 and there may be issues with compilers/etc if you only tested your code on your personal machine.

2. Be sure to push the final version of your code to your private Github repository. That will be the code you will submit.

3. Go to gradescope and find PA2 submission. You will be asked to authorize your github account. After authorizing your account, choose the repo you pushed your PA2 code to and the correct branch.

4. You can submit as many times as you like before the deadline: only your last submission will be counted.

5. Go to gradescope and find PA2 assignment. If you successfully submitted your PA1 (we hope you did!) then you should not have to authorize your github account again, but if you never submitted PA1 using git then you will be asked to authorize your github account. After authorizing your account, choose the repo you pushed your PA2 code to and the correct branch.

Good luck and have fun! :D
