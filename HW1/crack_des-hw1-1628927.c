#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <rpc/des_crypt.h>

typedef struct handler_args_s {
  char* input;
  int encrypted_size;
  char* plain;
  int start;
} handler_args_t;

double get_cpu_time() {
    return (double)clock() / CLOCKS_PER_SEC;
}

void print_char(char x) {
  int i;
  for(i = 0;i < 7;i++) { //the last bit is the parity bit
    printf("%d",((x >> i) & 1));
  }
  printf("X");
}

int add_padding(char* message) {
  int length = strlen(message) + 1;
  int remainder = length % 8;
  char* padded_message;

  int padded_length = remainder == 0 ? length : length + 8 - remainder;
  padded_message = (char*)malloc(sizeof(char)*padded_length);
  memcpy(padded_message,message,length);

  while (length < padded_length) {
      padded_message[length++] = '\0';
  }
  message = padded_message;
  return padded_length;
}

char* des_encrypt_cbc(char* key, char* input,int length) {
  char ivec[9];
  sprintf(ivec,"87654321");

  int result;

  char* cipher = (char*) malloc(sizeof(char) * length);
  memcpy(cipher,input,length);

  des_setparity(key);

  result = cbc_crypt(key, cipher, length, DES_ENCRYPT, ivec);
  return cipher;
}

char* des_decrypt_cbc(char* key, char* input,int length) {
  char ivec[9];
  sprintf(ivec,"87654321");

  int result;

  char* plain = (char*) malloc(sizeof(char) * length);
  memcpy(plain,input,length);

  des_setparity(key);

  result = cbc_crypt(key, plain, length, DES_DECRYPT, ivec);
  return plain;
}

void crack_des(void* arg) {
  handler_args_t* args = (handler_args_t*)arg;
  char* input = args->input;
  char* plain = args->plain;
  int encrypted_size = args->encrypted_size;
  int start = args->start;
  int from = (int)start;
  int to = from + 0x80;
  int length = strlen(input);
  char* cracked_message = (char*) malloc(sizeof(char)*(length));

  char* key = (char*)malloc(sizeof(char)*8);

  unsigned long counter = 0;

  key[0] = 0xff;
  key[1] = 0xff;
  key[2] = 0xff;
  key[3] = 0x00;
  key[4] = 0x00;
  key[5] = 0x00;
  key[6] = 0x00;
  key[7] = 0x00;

  int i,j,k,l,m,n,o,p;
  /*double cpu_start ,cpu_end, cpu_time;
  cpu_start = get_cpu_time();
  for(i=from;i<to;i+=2) {
    counter++;
    key[7] = i;

    cracked_message = des_decrypt_cbc(key,input,encrypted_size);

    if(strcmp(cracked_message,plain) == 0) {
      cpu_end = get_cpu_time();
      cpu_time = cpu_end - cpu_start;
      printf("CPU time: %f\n",cpu_time);

      printf("Found match after %d tries\n",counter);
      printf("Key used: ");
      int b;
      char byte;
      for(b=0;b<8;b++) {
        byte = key[b];
        print_char(byte);
        printf(" ");
      }
      printf("\n");
      printf("Cracked_message is %s\n",cracked_message);
      return;
    }
    free(cracked_message);

  }
  printf("Guess not found\n");
  return;*/

  /*double cpu_start ,cpu_end, cpu_time;
  cpu_start = get_cpu_time();
  for(i=from;i<to;i+=2) {
    for(j=from;j<to;j+=2) {
      counter++;
      key[6] = i;
      key[7] = j;

      cracked_message = des_decrypt_cbc(key,input,encrypted_size);

      if(strcmp(cracked_message,plain) == 0) {
        cpu_end = get_cpu_time();
        cpu_time = cpu_end - cpu_start;
        printf("CPU time: %f\n",cpu_time);

        printf("Found match after %d tries\n",counter);
        printf("Key used: ");
        int b;
        char byte;
        for(b=0;b<8;b++) {
          byte = key[b];
          print_char(byte);
          printf(" ");
        }
        printf("\n");
        printf("Cracked message is %s\n",cracked_message);
        return;
      }
      free(cracked_message);
    }
  }
  printf("Guess not found\n");
  return;*/

  /*double cpu_start ,cpu_end, cpu_time;
  cpu_start = get_cpu_time();
  for(i=from;i<to;i+=2) {
    for(j=from;j<to;j+=2) {
      for(k=from;k<to;k+=2) {
        counter++;
        key[5] = i;
        key[6] = j;
        key[7] = k;

        cracked_message = des_decrypt_cbc(key,input,encrypted_size);

        if(strcmp(cracked_message,plain) == 0) {
          cpu_end = get_cpu_time();
          cpu_time = cpu_end - cpu_start;
          printf("CPU time: %f\n",cpu_time);

          printf("Found match after %d tries\n",counter);
          printf("Key used: ");
          int b;
          char byte;
          for(b=0;b<8;b++) {
            byte = key[b];
            print_char(byte);
            printf(" ");
          }
          printf("\n");
          printf("Cracked message is %s\n",cracked_message);
          return;
        }
        free(cracked_message);
      }
    }
  }

  printf("Guess not found\n");
  return;*/

  /*double cpu_start ,cpu_end, cpu_time;
  cpu_start = get_cpu_time();
  for(i=from;i<to;i+=2) {
    for(j=from;j<to;j+=2) {
      for(k=from;k<to;k+=2) {
        for(l=from;l<to;l+=2) {
          counter++;
          key[4] = i;
          key[5] = j;
          key[6] = k;
          key[7] = l;

          cracked_message = des_decrypt_cbc(key,input,encrypted_size);

          if(strcmp(cracked_message,plain) == 0) {
            cpu_end = get_cpu_time();
            cpu_time = cpu_end - cpu_start;
            printf("CPU time: %f\n",cpu_time);

            printf("Found match after %d tries\n",counter);
            printf("Key used: ");
            int b;
            char byte;
            for(b=0;b<8;b++) {
              byte = key[b];
              print_char(byte);
              printf(" ");
            }
            printf("\n");
            printf("Cracked message is %s\n",cracked_message);
            return;
          }
          free(cracked_message);
        }
      }
    }
  }

  printf("Guess not found\n");
  return;*/

  double cpu_start ,cpu_end, cpu_time;
  cpu_start = get_cpu_time();
  for(i=from;i<to;i+=2) {
    for(j=from;j<to;j+=2) {
      for(k=from;k<to;k+=2) {
        for(l=from;l<to;l+=2) {
          for(m=from;m<to;m+=2) {
            counter++;
            key[3] = i;
            key[4] = j;
            key[5] = k;
            key[6] = l;
            key[7] = m;

            cracked_message = des_decrypt_cbc(key,input,encrypted_size);

            if(strcmp(cracked_message,plain) == 0) {
              cpu_end = get_cpu_time();
              cpu_time = cpu_end - cpu_start;
              printf("CPU time: %f\n",cpu_time);

              printf("Found match after %d tries\n",counter);
              printf("Key used: ");
              int b;
              char byte;
              for(b=0;b<8;b++) {
                byte = key[b];
                print_char(byte);
                printf(" ");
              }
              printf("\n");
              printf("Cracked message is %s\n",cracked_message);
              return;
            }
            free(cracked_message);
          }
        }
      }
    }
  }

  printf("Guess not found\n");
  return;

  /*double cpu_start ,cpu_end, cpu_time;
  cpu_start = get_cpu_time();
  for(i=from;i<to;i+=2) {
    for(j=from;j<to;j+=2) {
      for(k=from;k<to;k+=2) {
        for(l=from;l<to;l+=2) {
          for(m=from;m<to;m+=2) {
            for(n=from;n<to;n+=2) {
              counter++;
              key[2] = i;
              key[3] = j;
              key[4] = k;
              key[5] = l;
              key[6] = m;
              key[7] = n;

              cracked_message = des_decrypt_cbc(key,input,encrypted_size);

              if(strcmp(cracked_message,plain) == 0) {
                cpu_end = get_cpu_time();
                cpu_time = cpu_end - cpu_start;
                printf("CPU time: %f\n",cpu_time);

                printf("Found match after %lu tries\n",counter);
                printf("Key used: ");
                int b;
                char byte;
                for(b=0;b<8;b++) {
                  byte = key[b];
                  print_char(byte);
                  printf(" ");
                }
                printf("\n");
                printf("Cracked message is %s\n",cracked_message);
                return;
              }
              free(cracked_message);
            }
          }
        }
      }
    }
  }

  printf("Guess not found\n");
  return;*/


}

int main(void) {

  char key[9] = {0xFF,0xFF,0xFF,0x02,0xff,0xFF,0xFF,0xff};

  char* message = "AttackAtDawn";

  int message_padded_length = add_padding(message);
  printf("Message is %s\n",message);
  printf("Encrypted: ");
  char* cipher = des_encrypt_cbc(key,message,message_padded_length);
  printf("%s\n",cipher,strlen(cipher));

  int encrypted_size = add_padding(cipher);
  char* plain = des_decrypt_cbc(key,cipher,encrypted_size);
  printf("Decrypted is: %s\n",plain,strlen(plain));

  pthread_t thread1;
  pthread_t thread2;

  handler_args_t* thread_args1 = malloc(sizeof(handler_args_t));
  thread_args1->input = cipher;
  thread_args1->encrypted_size=encrypted_size;
  thread_args1->plain=plain;
  thread_args1->start=0;

  handler_args_t* thread_args2 = malloc(sizeof(handler_args_t));
  thread_args2->input = cipher;
  thread_args2->encrypted_size=encrypted_size;
  thread_args2->plain=plain;
  thread_args2->start=0x80;

  pthread_create(&thread1,NULL,(void*)crack_des,(void*)thread_args1);
  pthread_create(&thread2,NULL,(void*)crack_des,(void*)thread_args2);

  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);

  pthread_exit(0);
}
