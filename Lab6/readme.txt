Name:  Mudith Mallajosyula
UID:   404937201
Lab    2


First, I retrieved and unzipped the SRT archive

       wget http://web.cs.ucla.edu/classes/fall18/cs35L/assign/srt.tgz
       tar -xvf str.tgz

Then, I added the import statement for pthread.h into main.c and added lpthread
to the LDLIBS target of the makefile.

To make the ray-tracing program multithreaded, I first had to make the image
processing part of the main function into its own helper function so that it
could be passed to the pthread_create function. To do this and ensure that each
thread could access the array of pixel data, I created a global 3-D array to
hold the data.

I also created global variables for the nthreads and scene variables, since
those would be needed in each thread.

To make the best use of parallelism, I split the pixels in the array into even
increments of width/nthreads. This way, each row of xs would be split between
the threads, since they are independent of eachother.

The last thread would span the remainder of the xs, in case width/nthreads was
truncated.

The result of the parallelism was that the execution time of the ray-tracing
function was approximately halved as the number of threads doubled. The overhead
involved in creating and joining threads meant that, at higher thread-counts,
the increse in efficiency was less prominent.
