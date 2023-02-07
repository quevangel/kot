#ifdef _WIN32
#include <windows.h>
#define read _read
#define write _write
#else
#include <unistd.h>
#endif 
#define BUFFER_SIZE 4096
#include <assert.h>
#include <string.h>
char input_buffer[BUFFER_SIZE+1];
char output_buffer[BUFFER_SIZE+1];
int output_fd = 1;
int input_fd = 0;
char *input_ptr;
char *output_ptr;
typedef unsigned int uint;
void
fst_flush ()
{
  write (output_fd, output_buffer, output_ptr-output_buffer);
  output_ptr = output_buffer;
}
void
fst_write_char (char ch)
{
  *output_ptr++ = ch;
  if (!*output_ptr)
    {
      write (output_fd, output_buffer, BUFFER_SIZE);
      output_ptr = output_buffer;
    }
}
#define wchar fst_write_char
char
fst_read_char ()
{
  if (*input_ptr) return *input_ptr++;
  int read_bytes = read (input_fd, input_buffer, BUFFER_SIZE);
  input_buffer[read_bytes] = 0;
  input_ptr = input_buffer;
  return *input_ptr++;
}
void
fst_consume_char ()
{
  assert (*input_ptr);
  input_ptr++;
}
char
fst_peek_char ()
{
  if (*input_ptr) return *input_ptr;
  int read_bytes = read (input_fd, input_buffer, BUFFER_SIZE);
  input_buffer[read_bytes] = 0;
  input_ptr = input_buffer;
  return *input_ptr;
}
#define rchar (fst_read_char ())
void
fst_write_uint (uint n)
{
  static char digs[24];
  uint nodigs = 0;
  do
    {
      int div = n/10;
      int d = '0' + n - div * 10;
      digs[nodigs++] = d;
      n = div;
    }
  while (n);
  while (nodigs)
    {
      fst_write_char (digs[--nodigs]);
    }
}
#define wuint fst_write_uint
int
fst_read_uint ()
{
  int res = 0;
  char ch;
 nextone:
  ch = fst_peek_char ();
  switch (ch)
    {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      res *= 10;
      res += ch - '0';
      fst_consume_char ();
      goto nextone;
    default: return res;
    }
}
#define ruint (fst_read_uint ())
__attribute__ ((constructor)) void
fst_init ()
{
  output_ptr = output_buffer;
  memset (output_buffer, -1, BUFFER_SIZE);
  output_buffer[BUFFER_SIZE] = 0;
  input_ptr = input_buffer;
  input_ptr[0] = 0;
}
