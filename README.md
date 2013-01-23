calendar_server
===============

The idea is to create a calendar server based on TCP. You need to define a protocol (i.e., define how
messages are formatted and transmitted), implement it, and write a client and a server that
communicate using your new connection-oriented protocol. Your protocol should support the
following functionalities:

  1. Add a new calendar event.
  2. Remove a calendar event.
  3. Update an existing calendar event.
  4. Get the events for a specific time or time range.

There are no other requirements regarding the protocol, i.e., you are free to decide the protocol
details, e.g., the message structure and content for the client/server communication.
Client Implementation

The client is a simple program that takes several arguments and contacts the server and prints the
response received from the server. The syntax for the client should be:

  A: Adding an event: ./mycal hostname port myname add 031505 0800 0900 Exam
  B: Removing an event: ./mycal hostname port myname remove 031505 0800
  C: Updating an event: ./mycal hostname port myname update 031505 0800 1000 OralExam
  D: Getting an event 1: ./mycal hostname port myname get 031505 0800
  E: Getting an event 2: ./mycal hostname port myname get 031505

In all cases 'myname' is a string that identifies a user (e.g., login name). In (A), you specify the date,
the beginning and end time of the event, and a single word identifying the type of event (e.g., exam,
doctor, trip, meeting, ...). You can assume that no event can go beyond 2400 of the same day (i.e.,
every event has to be finished by midnight at the latest). If there is a conflict with another already
stored event, the client will be notified by the server and the client informs the user (e.g. "Conflict
detected!"). In (B), you specify the date and the beginning time of an event, if successful the client
will receive an acknowledgment from the server, if the event does not exist, the client will be
notified by the server and the client informs the user. In (C), you specify an event as in (A),
however, either the ending time or the event type has to be different (or both). Again, the client will
inform the user if the operation was successful. In (D), the server returns the type of the event
requested, if the event does not exist, the client informs the user. Finally, in (E), if only the date is
specified, all events of that day are returned.
Further, the server's hostname and port number have to be passed to the client as command line
arguments.


Server Implementation

The server waits for requests from clients. Each user's ('myname') events are stored separately from
other users (either in a data structure or a file, e.g., 'myname.cal'). If files are used, the file should be
created when the first event is set and should be deleted when the last remaining event is deleted or
expired. You are required to provide three different server implementations:
  
  • Iterative Approach: Here, only one client request is handled at any given time and only one
server process/thread exists.
  
  • Approach Based on Select(): Again a single-threaded server is used, but the server can
handle multiple clients (and open sockets) with the select() system call. Further, the protocol
has to provide one additional functional: "get all events for a given client". The syntax of
this new command is: ./mycal hostname port myname getall. The client first asks the server
how many entries the calendar file has for the client 'myname' and if the response is nonzero,
the client requests each entry individually, with 2 seconds delay between requests. Once all
events have been received, the client notifies the server of the end of the connection.
  
  • Multi-Threaded Approach: Here, multiple processes or threads are used to handle requests
in parallel (i.e., each new request is handled by a newly created process or thread). Again,
the protocol should support the "getall" command.

Error Handling

The following error handling is expected: all return values of the system calls have to be checked,
also check the correct number of command-line parameters for the client and the correct date and
time format (also make sure that the end time of an event is later than the begin time). Whenever the
server responds to a request, it should also remove ALL expired events for ALL users. Compile
your code with the '-Wall' flag and make sure to remove all warnings.
