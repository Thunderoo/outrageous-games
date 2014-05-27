import cherrypy

cherrypy.server.socket_host = '0.0.0.0'

class HelloWorld(object):
    @cherrypy.expose
    def index(self):
        host = cherrypy.request.headers['Host']
        return "You have successfully reached " + host

cherrypy.quickstart(HelloWorld())
