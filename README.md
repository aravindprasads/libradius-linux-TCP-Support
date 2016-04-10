libradius-linux TCP support
===========================

This is a fork of libradius-linux repo - https://github.com/speakinghedge/libradius-linux (LINUX port of recent (juniper)-libradius offered by FreeBSD.) 

Cause:

Libradius supports only UDP as transport protocol for RADIUS Messages. Recently, RADIUS Servers have started supporting TCP. Hence, added support for using TCP in Libradius. 

Sample Files:

> RADIUS Client File - src/tcp-client.c

> radius.conf file - src/radius.conf 

Synopsis of Changes made:

1) radius.conf file:

	> Actual radius.conf provided by libradius - http://www.freebsd.org/cgi/man.cgi?query=radius.conf 
	> Now, radius.conf file should include the Transport protocol type to be used (TCP/UDP):
		>> Include it as Fourth Field in radius.conf file. 
			auth  auth.domain.com:1645	 "I can't see you" tcp 5 4 
		>> Hence, currently we have 4 compulsory parameters in radius.conf file - Service type, Server host, Shared secret, Transport Protocol Type.
	
2) Change in prototype of rad_add_server() and rad_add_server_ex() APIs. 

The protocol field is appended to the already existing list of parameters in the APIs. 

	> rad_add_server (struct rad_handle *h, const	char *host, int	port, const char *secret, int timeout, int max_tries, char *protocol)
	
	> rad_add_server_ex (struct rad_handle *h, const	char *host, int	port, const char *secret, int timeout, int max_tries, char *protocol)
	
	> Pass the following strings for specifying the Transport Protocol type for the "protocol" parameter in above APIs 
		>> "udp" for UDP protocol
		>> "tcp" for TCP Protocol

3) Reason for forced change in Standard radius.conf file: 

	> Currently, only 3 parameters are compulsory - Service type, Server host, Shared secret and the rest are optional. 
	> Needed to add Transport Protocol as the fourth parameter so that rest of parameters behind it remain optional as previously existed. 
