libradius-linux TCP support
===========================

This is a fork of libradius-linux repo - https://github.com/speakinghedge/libradius-linux (LINUX port of recent (juniper)-libradius offered by FreeBSD.) 

Cause:

Till now, Libradius supports only UDP as transport protocol for RADIUS Messages. Now, RADIUS Servers have started supporting TCP. Hence, added support for TCP at the RADIUS Client. 

Samples:

> Sample RADIUS Client File - src/tcp-client.c

> radius.conf file - src/radius.conf file

Synopsis of Changes made:

1) radius.conf file:

	> Actual radius.conf provided by libradius - http://www.freebsd.org/cgi/man.cgi?query=radius.conf 
	> Now, radius.conf file should include the Transport protocol type to be used (TCP/UDP):
		>> Include it as Fourth Field in radius.conf file. 
			auth  auth.domain.com:1645	 "I can't see you" tcp 5 4 
		>> Hence, currently we have 4 compulsory parameters in radius.conf file - Service type, Server host, Shared secret, Transport Protocol Type.
	
	> Change in prototype of rad_add_server() and rad_add_server_ex() APIs. 
		>> rad_add_server (struct rad_handle *h, const	char *host, int	port, const char *secret, int timeout, int max_tries, char *protocol)
		>> rad_add_server_ex (struct rad_handle *h, const	char *host, int	port, const char *secret, int timeout, int max_tries, char *protocol)
		
		
2) Reason for forced change in Standard radius.conf file: 

	> Currently, only 3 parameters are compulsory - Service type, Server host, Shared secret and the rest are optional. 
	> Needed to add Transport Protocol as the fourth parameter so that rest of parameters behind it remain optional as previously existed. 
