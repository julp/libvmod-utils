## Installation

First, you'll need:
* varnish sources (same exact version)
* cmake

Then, to build this module:
```
cd .../libvmod-utils/
cmake . -DVARNISHSRC:PATH=/path/to/varnish/sources # or build it into an other directory
make
(sudo) make install
```

## Functions

* `STRING resolve(IP)`: do a reverse resolution to get (if available) hostname for the given address
* `STRING normalize_qs(STRING)`: remove empty query string, could also be replaced by `set req.url = regsub(req.url, "\?$", "");` which do not require any vmod
* `STRING remove_qs(STRING)`: remove query string, could also be replaced by `set req.url = regsub(req.url, "\?.*", "");` which do not require any vmod
* `BOOL startswith(STRING, STRING)`: does a string start with a given prefix?
* `BOOL endswith(STRING, STRING)`: does a string end with a given suffix?

resolve function may be useful to recognize some bots like msn/bing, eg:
```
# User-Agent: Mozilla/5.0 (compatible; bingbot/2.0; +http://www.bing.com/bingbot.htm)
# client claims to be a bingbot
if (req.http.user-agent ~ "bingbot") {
    # check if it is true, cf: http://www.bing.com/webmaster/help/how-to-verify-bingbot-3905dc26
    if (utils.resolve(client.ip) ~ "\.search\.msn\.com$") {
        # this is the case
    } else {
        # client lies
    }
}
```
