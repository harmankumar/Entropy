#include <bits/stdc++.h>

#define SAFETY_TIMEOUT 65
#define botname = 'BigDaddy'	 //PLEASE CHOOSE A UNIQUE BOTNAME
#define server_address = 'localhost'
#define server_port = 8000
#define pathToRun = 'run.sh' 

using namespace std;

bool aiProc = false;
bool advStdout = false;

void resetCode(args)
{		
	if (aiProc):
		aiProc.kill()
		
	aiProc = Popen (['sh', pathToRun], stdin = PIPE, stdout = PIPE, bufsize=0)
	advStdout = NBSR(aiProc.stdout)
}

void updateCode(args):
{
	try:
		aiProc.stdin.write(args['payload'])
		my_move = advStdout.readline(SAFETY_TIMEOUT)
	except:
		print 'Something bad happened with the client (# need to kill it?)'
		my_move = false;
	
	print 'My move (%s): %s'%(botname, my_move)
	if(!my_move)
		payload = json.dumps({'status': False, 'comment': 'timeout'})
	else:
		payload = json.dumps({'payload': my_move, 'status': True})

	clientsocket.send(payload)
}

int main(int argc, char** argv)
{
	int server_port, server_address;
	float delay;
	string botname, pathToRun;

	if (argc > 1):
		server_port = int(sys.argv[1])

	if (argc > 2):
		server_address = sys.argv[2]

	if (argc > 3):
		botname = sys.argv[3]

	if (argc > 4):
		pathToRun = sys.argv[4]

	if (argc > 5):
		delay = float(sys.argv[5])
		time.sleep(delay)

	return 0;
}