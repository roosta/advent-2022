#define BUFSIZE 16
#define MAXLEN 2500

extern char buf[MAXLEN][BUFSIZE];
extern int length[MAXLEN];
extern int height;

int get_line(char s[]);
void readbuf(void);
