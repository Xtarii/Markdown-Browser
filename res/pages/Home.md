# Markdown Browser

A Browser Made for markdown



#### Searching
When searching using the Markdown browser simply type
the address into the bar on the top.

An example would be **mdtp://local:55/test**.
- **mdtp** is the protocol used and is ended with **://**
- **local** is the domain
- **55** is the port used and seperated with **:**
- **/test** is the commando

A domain name can be entered without a port.
- **mdtp.server.com/**

A full mdtp url would then look like **mdtp://mdtp.server.com/**



Normally the command is the page that should be entered, but
that is up to the server to decide.
It may also be possible to use extra data, **query parameter**, when
searching. They are entered after the commando.
- **/test?name=Jordan**

It is up to the server to implement query parameters.
