This repository contains my parallel implementation of FastJet 3.0.6.
This parallel implementation uses a class called ThreadManager, which
has internal states that regulate the use of concurrency and multithreading.
ThreadManager has two main states: singleCore and multiCore.  Both of these
are member functions which instruct fastjet whether or not to use threads
and memory buffers while clustering.

//------------------------------------------------------------//

The three .cpp files inside the event_reconstruction folder are used to process
event data.  The three files are:

   original_fastjet_constructor.cpp
      //uses the non-ThreadManager ClusterSequence constructor

   singlecore_thereadmanager.cpp
      //uses the newly created ThreadManager constructor
      //to execute a one-core ClusterSequence


   multicore_threadmanager.cpp
      //uses the newly created ThreadManager constructor
      //to execute a multithreaded ClusterSequence

Inside each of these files are instructions on how to compile and run via g++.

//------------------------------------------------------------//

To install this version of fastjet, use the following commands via Terminal:
(from the fastjet-3.0.6 directory:)

$    sudo ./configure --prefix=$PWD/../fastjet-install CXXFLAGS=-std=c++11 LIBS=-lpthread  && sudo make && sudo make install && sudo make check

//------------------------------------------------------------//
<<<<<<< HEAD

=======
>>>>>>> 868c162cd14f77c25ada10fd1976f6a8c5c581de
