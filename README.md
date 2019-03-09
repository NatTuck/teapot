
Project Teapot

Can I turn an RC car into an robot car?

Probably.

Repo structure:

Servers:

 * sim/ - Gazebo simulator setup for the robot.
 * real/ - Drivers for the physical robot.

Clients

 * brain/ - Client supporting both manual and automatic control.

Repo contents without other attribution or licence info copyright (C) 2018 Nat
Tuck and licenced under the GNU GPLv3 or later.

Client-server protocol:

 * Server listens on TCP port.
 * Client connects.
 * Messages are 32-bit length + msgpack msg.
 * Messages can be sent in any order, with any initiator; no responses.
 * Messages are map of string keys including timestamp.

Messages:

General form { topic: String, data: Msg, time: Timestamp }

Either side can subscribe to topics. Messages are only sent to
subscribers.

 * { topic: "subscribe", data: [Topics] }
 * { topic: "unsubscribe", data: [Topics] }

Server -> Client topics (mostly sensors):

 * lidar - [{Angle, Distance}]
 * depth -  
 * compass
 * accelerometer
 * encoder

Client -> Server topics (mostly commands):

 * control {speed, 
 * 
 
 
 
