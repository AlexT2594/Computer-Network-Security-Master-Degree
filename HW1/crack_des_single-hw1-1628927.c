#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <rpc/des_crypt.h>

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

void print_string_hex(char* string,int length) {
  int i;
  for(i = 0;i<length;i++) {
    printf("%x ",string[i]);
  }
  printf("\n");
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

char* crack_des(char* input,int encrypted_size,char* plain) {
    int length = strlen(input);
    char* cracked_message = (char*) malloc(sizeof(char)*(length));

    char* key = (char*)malloc(sizeof(char)*8);

    unsigned long counter = 0;

    key[0] = '0';
    key[1] = '1';
    key[2] = '2';
    key[3] = 0x00;
    key[4] = 0x00;
    key[5] = 0x00;
    key[6] = 0x00;
    key[7] = 0x00;

    int i,j,k,l,m,n,o,p;
    /*double cpu_start ,cpu_end, cpu_time;
    cpu_start = get_cpu_time();
    for(i=0x00;i<0x100;i+=2) {
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

        return cracked_message;
      }
      free(cracked_message);

    }

  return "Guess not found\n";*/

    /*double cpu_start ,cpu_end, cpu_time;
    cpu_start = get_cpu_time();
    for(i=0x00;i<0x100;i+=2) {
      for(j=0x00;j<0x100;j+=2) {
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
          return cracked_message;
        }
        free(cracked_message);
      }
    }

    return "Guess not found\n";*/

    /*double cpu_start ,cpu_end, cpu_time;
    cpu_start = get_cpu_time();
    for(i=0x00;i<0x100;i+=2) {
      for(j=0x00;j<0x100;j+=2) {
        for(k=0x00;k<0x100;k+=2) {
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
            return cracked_message;
          }
          free(cracked_message);
        }
      }
    }

    return "Guess not found\n";*/

    /*double cpu_start ,cpu_end, cpu_time;
    cpu_start = get_cpu_time();
    for(i=0x00;i<0x100;i+=2) {
      for(j=0x00;j<0x100;j+=2) {
        for(k=0x00;k<0x100;k+=2) {
          for(l=0x00;l<0x100;l+=2) {
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
              return cracked_message;
            }
            free(cracked_message);
          }
        }
      }
    }

    return "Guess not found\n";*/

    double cpu_start ,cpu_end, cpu_time;
    cpu_start = get_cpu_time();
    for(i=0x20;i<0x80;i+=2) {
      for(j=0x20;j<0x80;j+=2) {
        for(k=0x20;k<0x80;k+=2) {
          for(l=0x20;l<0x80;l+=2) {
            for(m=0x20;m<0x80;m+=2) {
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
                return cracked_message;
              }
              free(cracked_message);
            }
          }
        }
      }
    }

    return "Guess not found\n";

    /*double cpu_start ,cpu_end, cpu_time;
    cpu_start = get_cpu_time();
    for(i=0x20;i<0x80;i+=2) {
      for(j=0x20;j<0x80;j+=2) {
        for(k=0x20;k<0x80;k+=2) {
          for(l=0x20;l<0x80;l+=2) {
            for(m=0x20;m<0x80;m+=2) {
              for(n=0x20;n<0x80;n+=2) {
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
                  return cracked_message;
                }
                free(cracked_message);
              }
            }
          }
        }
      }
    }

    return "Guess not found\n";*/


}

int main(void) {
  srand(time(NULL));
  /*printf("Attacking DES\nTesting encryption and decryption:\n");
  int MAX_LENGTH = 100;
  char test_string[MAX_LENGTH];
  int counter,i,message_padded_length;
  char key[9];
  char byte;
  for(counter=1;counter<MAX_LENGTH;counter++) {
    for(i = 0;i<counter;i++){
      test_string[i] = rand();
    }
    test_string[i] = '\0';
    printf("Random message is: ");
    print_string_hex(test_string,i);
    for(i=0;i<8;i++) {
      key[i] = rand();
    }
    printf("Random key is:");
    for(i=0;i<8;i++) {
      byte = key[i];
      print_char(byte);
      printf(" ");
    }
    printf("\n");
    message_padded_length = add_padding(test_string);
    char* ciphertext = des_encrypt_cbc(key,test_string,message_padded_length);
    printf("Encryption gives us: ");
    print_string_hex(ciphertext,message_padded_length);
    char* plaintext = des_decrypt_cbc(key,ciphertext,message_padded_length);
    printf("Decyption gives us: ");
    print_string_hex(plaintext,counter);
    if(strcmp(test_string,plaintext) == 0) {
      printf("Test %d passed! Decryption is the same as the original test string.\n",counter);
    } else{
      printf("Test %d NOT passed! Decryption is not the same as the original test string.\n",counter);
    }
    printf("\n");
  }*/

  char key[9] = {'0','1','2','3','4','5','6','7'};

  char* message = "AttackAtDawn";

  int message_padded_length = add_padding(message);
  printf("Message is %s\n",message);

  char* cipher = des_encrypt_cbc(key,message,message_padded_length);
  char* plain = des_decrypt_cbc(key,cipher,message_padded_length);

  char* cracked_message = crack_des(cipher,message_padded_length,message);
  printf("Cracked message is %s\n", cracked_message);

  return 0;
}
