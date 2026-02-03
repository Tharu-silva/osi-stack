When processing IP packets, we need to collect packets until a full datagram 
can be assembled. Only then can we move onto the transport layer, if the current
packet does not complete a datagram then return early. 