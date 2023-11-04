# ddr_late_
late submission of duckduckgo app


This application prints duck duck go utilizing 4 thread:

Duck1_THREAD - delays betweeen 1-2 seconds (pseudo random), then print the first duck 
Duck2_THREAD - delays between 2-3 seconds, then prints the second duck
Goose_THREAD -delays between 3-4 seconds, then prints goose
Main_THREAD -Controls order of execution of threads

Main registers callbacks with all 3 print threads, then controls execution order. First signally to trigger delay, then signalling to trigger print, then waits for the callback proceeding with next word delay then print. Main inserts commas and
newlines to eas reading.

Assumption:
Assumed (on this submission) that delays were peformed AFTER previous word print (e.g. after goose prints start 1-2 second delay and wait before printing first duck)


Still room to clean up code, add error protection and ensure more testing. Was tested to build. Includes should be moved to one folder... Bonus File for random number generation was added. 

