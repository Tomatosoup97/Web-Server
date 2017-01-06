# Simple HTTP Web Server

Simple version of HTTP Web Server.

## Upcoming features:
1. Persistent connection (keep-alive)
1. HTTP version 1.1 compatibility
1. Platform Independent
1. Supported HTTP verbs (methods):
    * GET
    * POST
    * HEAD
1. Listens on default HTTP port 80
1. Serve HTML documents

## Arrangements
_which might not be accomplished_:

1. HTTPS - Secure connection by TLS using OpenSSL libraries
1. Support HTTP 2.0
1. Create a better interface for RESTful services
1. Make support for more HTTP verbs:
    * OPTIONS, PUT, PATCH, DELETE
1. Listen on port defined by user (e.g 8000)
1. Allow multiple resources types by adding Content-Type HTTP header:
    * JSON (Header: application/json)
1. XML (Header: application/xml)

## Libraries:

* Socket – C++ library for handling connection
* Boost Asio – One of the Boost's portable C++ source libraries. This library is serves a rich interface and API for network programming
