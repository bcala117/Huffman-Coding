The first part works pretty much exactly as intended but could use a fair amount of work and polishing. 

In Part 2 there are a few errors and weird things I had to do with the code in order to get the program working.

	- In the "Huffman.h" Header file I had two int variables named previous and product that I needed
	  to use in multiple loactions but they needed to be initialized prior to use in those locations so due
	  to time constraints the only way I figured out how to get around this was to declare and unnamed 
	  namespace for the entire program in this file since the other 2 files are including this one. 
	
	- In the "Huffman.cpp" file inside of the decoding function i was getting an error with the if statement
	  on line 60. When I was reading the information I was getting the erros that the string subscript
	  was out of range and that it was caused by an invalid parameter being passed into it. I could not 
	  figure out hwhat exactly was triggering this to occur because it seemed to depend on the contents 
          of some of the input files so when I was messing around with changing the text in them and i put a try/
	  catch statement around it and it seems to work but is probably very much a bandaid on this issue. 

	- Also the decoding seems to be slightly off by a little bit but I couldnt figure the problem out in time.