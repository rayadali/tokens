/*
 * tokenizer.c
 *Rayad Ali
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
//typedef struct TokenizerT_{
    //char separatorChars[50]; // first command line string storage
   // char tokens[]; //second command line string.  pass by reference
    // using pointers as required in the PDF outline
    char *separators;
    char *tokens;
    int index;
};
/*
newline (0x0a) \n
horizontal tab (0x09) \t
vertical tab (0x0b) \v
backspace (0x08) \b
carriage return (0x0d) \r
form feed (0x0c) \f
audible alert (0x07) \a
backslash (0x5c) \\
double quote (0x22) \”
*/

char escapes[10] = "\n\t\v\b\r\f\a\\\""; // store the escape characters
//char escapes[10] = "ntvbrfa\\\""; // store the escape characters

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

//my notes for using arrow notation
//foo->bar is equivalent to (*foo).bar -- it gets the member called bar from the struct that foo points to.
TokenizerT *TKCreate(char *separators, char *ts) {
/* this was code before I started using pointers    
int ;
    //count number of separators
//create array
char sepArray[strlen(separators)]; // length is determined by the length of string passed into the function
int countSep = 0; //keep count of the number and store, initialized to 0
*/

// using memcpy over strcpy for performance
// note for how malloc, memcpy works
// malloc creates a memory block of size in parameter
// void * memcpy ( void * destination, const void * source, size_t num );
//separators
    /*
    TokenizerT *tokeniser;
    tokeniser = (TokenizerT *) malloc(sizeof *tokeniser);
    size_t slength;
    slength = strlen(separators) + 1;
    char *sep;
    sep = malloc(slength);
    memcpy(sep, separators, slength);
    tokeniser->separators = sep;
     */
    
    //testing
    
    //printf("from create %s\n",separators);
    //printf("from create %s\n",ts);
    
    TokenizerT *tokeniser =  malloc(sizeof *tokeniser);
    size_t slength = (strlen(separators)+1);
    char *sep = malloc(slength); // creating memory space we add +1 for the \0
    memcpy(sep, separators, slength); // copies value in separators paramater passed into funtion to sep, length size of separators
    tokeniser->separators = sep;
    
    //testing
    //printf("after create separators are %s\n",sep);

//tokens
    size_t tlength = strlen(ts)+1;
    char *tok = malloc(tlength);
    memcpy(tok, ts, tlength);
    tokeniser->tokens = tok;
    
    //now account for escape characters


    char tokensEscToHex [strlen(ts)];// will essentially be the same token stream but with hex codes instead of escape chars
    int index = 0; //this will be keeping track of the index to be updated
    int countThroughTokens, countThroughEsc;
    for(countThroughTokens=0; countThroughTokens<strlen(ts); countThroughTokens++){
        if(ts[countThroughTokens]=='\n'){
            countThroughTokens++;
            for(countThroughEsc = 0; countThroughEsc<strlen(escapes); countThroughEsc++){
                if (escapes[countThroughEsc]==ts[countThroughTokens]) {
                    tokensEscToHex[index++] = '['; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'x'; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'a';
                    tokensEscToHex[index++] = ']'; 
                    break;
                }
            }
            continue;
        }
        if(ts[countThroughTokens]=='\t'){
            countThroughTokens++;
            for(countThroughEsc = 0; countThroughEsc<strlen(escapes); countThroughEsc++){
                if (escapes[countThroughEsc]==ts[countThroughTokens]) {
                    tokensEscToHex[index++] = '['; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'x'; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = '9';
                    tokensEscToHex[index++] = ']'; 
                    break;
                }
            }
            continue;
        }
        if(ts[countThroughTokens]=='\v'){
            countThroughTokens++;
            for(countThroughEsc = 0; countThroughEsc<strlen(escapes); countThroughEsc++){
                if (escapes[countThroughEsc]==ts[countThroughTokens]) {
                    tokensEscToHex[index++] = '['; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'x'; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'b';
                    tokensEscToHex[index++] = ']'; 
                    break;
                }
            }
            continue;
        }
        if(ts[countThroughTokens]=='\b'){
            countThroughTokens++;
            for(countThroughEsc = 0; countThroughEsc<strlen(escapes); countThroughEsc++){
                if (escapes[countThroughEsc]==ts[countThroughTokens]) {
                    tokensEscToHex[index++] = '['; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'x'; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = '8';
                    tokensEscToHex[index++] = ']'; 
                    break;
                }
            }
            continue;
        }
        if(ts[countThroughTokens]=='\r'){
            countThroughTokens++;
            for(countThroughEsc = 0; countThroughEsc<strlen(escapes); countThroughEsc++){
                if (escapes[countThroughEsc]==ts[countThroughTokens]) {
                    tokensEscToHex[index++] = '['; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'x'; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'd';
                    tokensEscToHex[index++] = ']'; 
                    break;
                }
            }
            continue;
        }
        if(ts[countThroughTokens]=='\f'){
            countThroughTokens++;
            for(countThroughEsc = 0; countThroughEsc<strlen(escapes); countThroughEsc++){
                if (escapes[countThroughEsc]==ts[countThroughTokens]) {
                    tokensEscToHex[index++] = '['; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'x'; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'c';
                    tokensEscToHex[index++] = ']'; 
                    break;
                }
            }
            continue;
        }
        if(ts[countThroughTokens]=='\a'){
            countThroughTokens++;
            for(countThroughEsc = 0; countThroughEsc<strlen(escapes); countThroughEsc++){
                if (escapes[countThroughEsc]=='\a') {
                    tokensEscToHex[index++] = '['; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'x'; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = '7';
                    tokensEscToHex[index++] = ']'; 
                    break;
                }
            }
            continue;
        }
        if(ts[countThroughTokens]=='\\'){
            countThroughTokens++;
            for(countThroughEsc = 0; countThroughEsc<strlen(escapes); countThroughEsc++){
                if (escapes[countThroughEsc]==ts[countThroughTokens]) {
                    tokensEscToHex[index++] = '['; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'x'; 
                    tokensEscToHex[index++] = '5'; 
                    tokensEscToHex[index++] = 'c';
                    tokensEscToHex[index++] = ']'; 
                    break;
                }
            }
            continue;
        }
        if(ts[countThroughTokens]=='\"'){
            countThroughTokens++;
            for(countThroughEsc = 0; countThroughEsc<strlen(escapes); countThroughEsc++){
                if (escapes[countThroughEsc]==ts[countThroughTokens]) {
                    tokensEscToHex[index++] = '['; 
                    tokensEscToHex[index++] = '0'; 
                    tokensEscToHex[index++] = 'x'; 
                    tokensEscToHex[index++] = '2'; 
                    tokensEscToHex[index++] = '2';
                    tokensEscToHex[index++] = ']'; 
                    break;
                }
            }
            continue;
        }
        else{
            
            tokensEscToHex[index++] = ts[countThroughTokens]; // otherwise character is not an escape character
            //hexIndex++;
        }
    }
    //printf("test1 %s\n",tokensEscToHex);
    size_t updatedTokensLength = strlen(tokensEscToHex);

    tokeniser->tokens = (char *)malloc(sizeof(char) * updatedTokensLength);
    //size_t updatedTokensLength = strlen(tokensEscToHex)+1;
    //printf("test2 %s\n",tokensEscToHex);
    memcpy(tokeniser->tokens,tokensEscToHex, updatedTokensLength);
    return tokeniser;
    
    //testing
    
    //printf("after create tokens are %s\n",tok);
    //testing with index method
    //tokeniser->index = 0;
    
  //return tokeniser;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
//  using the free function --deallocat memory allocated from malloc 
// how free works -- void free (void* ptr);
    free(tk->tokens); // free in reverse order of malloc
    free(tk->separators);
    free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */


/*
 * 
 * This was my old approach
 * New method uses another function to do the looping and printing
char *TKGetNextToken(TokenizerT *tk) {
//need to keep track of the separators given in the first string and exclude them from the second string
//possible implemention of the printing of each token on a new line in this section
    //creating variables
    char *nextToken = (char *)malloc(strlen(tk->tokens)+1);
    char *delimiter = (char *)malloc(strlen(tk->separators)+1);
    char *tokenPtr = (char *)malloc(strlen(tk->tokens)+1);
    char *check = (char *)malloc(sizeof(char));
    //char *delimiter, *tokenPtr, *check = NULL;
    char delim;
    // *tokenPtr = tk->tokens; //getting error 
    // *nextToken = NULL; // getting error
    tokenPtr = tk->tokens;
    nextToken = NULL;
    //int i;
    
    //error handling for empty second string
    if(!tk->tokens) return NULL;
    if(tk->tokens == '\0') return NULL;
    //scanning
    //while(tokenPtr[0] != '\0') //loop tokens string until end
    for(tk->index; tk->index<strlen(tokenPtr); tk->index++)
    {
        //test
        
        //printf("start of get next%s\n", tokenPtr);
        
        delimiter = tk->separators; //storing the separators to look out for
        //test
        int j = tk->index;
        delim = *(tokenPtr +j);
       // printf("current delim is %s \n", delim);
        
        
       // printf("our delimters are %s\n", delimiter);
        //printf("current index is %d \n", j);

        //if ((tk->tokens) == *delimiter){ //match , getting error 
        //if ((tk->tokens) == delimiter){ // trying something different
        int i = 0;
        for(i=0;i< strlen(delimiter)+1;i++){
        if(tk->tokens[tk->index] == delimiter[i]){
            *tokenPtr = tk->tokens[tk->index];
            //testing
            char k = tk->tokens[1];
                    printf("test 3 %s",k);
            printf("current char is %s\n",tokenPtr);
                    printf("test\n");
            //printf("current char is %s\n",(tk->tokens[tk->index]));
                    printf("test2\n");
                    
            //if(tokenPtr == check){ //new method
             */ /*
                            
            printf("test again\n");
            if(tk->tokens[tk->index] == check){
                check++;//skip this
                printf("skip");
                break; // end this iteration
            }
            else{
                printf("attempting here\n");
                *tokenPtr = '\0'; //set to null character
                tokenPtr++; //move to next
                //if((nextToken = malloc(sizeof check) + 1 * sizeof(char) != NULL)){ // getting error
                //if((*nextToken = malloc(sizeof check) + 1 * sizeof(char) != NULL)){
                if(nextToken != NULL){
                    printf("not null\n");
                    size_t tokenLength = strlen(check)+1; 
                    memcpy(nextToken, check, tokenLength); //getting the token and storing again using memcpy
                    tk->tokens = tokenPtr;
                    //testing
                    printf("end of%s\n",nextToken);
                    return nextToken;
                }
            }
        }
        else{
            printf("is it here?!\n");
            delimiter++; // check for next
            }
        }
        //tokenPtr++;// iterate to next delimiter taken out as I'm now using indexes
        if((nextToken = malloc(sizeof check) + 1 * sizeof(char)) != NULL){
        size_t tokenLength = strlen(check)+1; 
        memcpy(nextToken, check, tokenLength);
        printf("maybe here?\n");
    }
    tk->tokens = tokenPtr;
    return nextToken;
}
}
  */      



/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {
    //declaring & initialising pointers and variables
    char *tokensString = tk->tokens;
    int lengthOfTokenString = strlen(tokensString);
    char *delimiters = tk->separators; // at this point we can check if delimitors space is empty - in which case we can return the second string 
    int lengthOfDelimiters = strlen(delimiters);
    if (strlen(delimiters)==0) {
        return tokensString; // for empty string 1
    }
    char *nextToken = (char *)malloc(sizeof(char)); 
    int lengthOfCurrentToken;
    int countForTokens;
    int countForDelimiters;
    typedef enum { false, true } bool;
    bool check = false;
    
     
    
    //Want to check if any of the separators are in the tokens string
    //Create nested for loop uding variables declared above.
    
    for(countForTokens = 0; countForTokens<lengthOfTokenString; countForTokens++){
        char tokensIndex = *(countForTokens+tokensString); // storing the index of the token stream -  character in current iteration
        for(countForDelimiters = 0; countForDelimiters<lengthOfDelimiters; countForDelimiters++){
            char delimsIndex = *(countForDelimiters+delimiters); // storing the delimiter to be looked at
            lengthOfCurrentToken = strlen(nextToken); // we will be making changes to the pointers using the length
            
            if(delimsIndex==tokensIndex){   // here we have a match with the delim and our token!
                check = true; // keeping track of the match
                break; // only breaking out of inner loop as there might me multiple occurences in 2nd string
            }

        }
        if (check==true) {    //now that the delimiter has been found we can return the token up to that point
            return nextToken;
        }
        *(lengthOfCurrentToken+nextToken) = tokensIndex; // add character to token to be returned
    }
    lengthOfCurrentToken = strlen(nextToken); //update the length
    *(nextToken+lengthOfCurrentToken) = '\0';    //after coming out of the loops add the null character to the end of the token to be returned
    return nextToken;


  //return NULL;
}

void output(TokenizerT * token, int numOfCharacters){
    
    char *returnedToken = TKGetNextToken(token); //pass token into function, receieve token up to delimiter
    //printf("tmp hold %s\n", tmp);
    char *copy = (char *)malloc(sizeof(char)); // creating memory space
    size_t sepLength = (strlen(token->separators));
    memcpy(copy,token->separators,sepLength); // store separators into var  copy
    //printf("currently have this %s\n",copy);


    int returnedTokenLength = strlen(returnedToken)+1; // we need to know the length of the string
    numOfCharacters = numOfCharacters-returnedTokenLength; // The first token will be printed, so now we don't need that anymore, this updates the length of the tokens left
    char *output = (char *)malloc(sizeof(char)); // this is what we will be outputting
    size_t tokenLength = (strlen(token->tokens));
    memcpy(output,token->tokens + returnedTokenLength, tokenLength);
    //I have a separate print function as defined below
    //This prints out the token before the first delimiter
    


    if(strlen(returnedToken)>0){
        printf("%s\n", returnedToken);
    }
    TKDestroy(token); // free the dynamic allocated memory
    // here we recurse through the token stream until the end
    // we can now print out the tokens after the 1st delimiter using this
    token = TKCreate(copy, output); //initialise with the updated tokens and the initial set of delimiters
    while(numOfCharacters>0){
        returnedToken = TKGetNextToken(token); // receive next token
        if(strlen(returnedToken)>0){ //print that token if it is non empty
            printf("%s\n", returnedToken);
        }
        returnedTokenLength = strlen(returnedToken)+1; // this and the next line update the tokens left to be printed
        numOfCharacters = numOfCharacters-returnedTokenLength;
        free(output);// updating the output string
        output = (char *)malloc(sizeof(char));
        memcpy(output,token->tokens + returnedTokenLength, tokenLength);
        TKDestroy(token); //free 
        token = TKCreate(copy, output);
    }

    TKDestroy(token); //the final freeing after we are finished!
    return;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
    
    // testing
    //char name[]="ray";
    //printf("%s\n",name);
    //testing
    
    
    if (argc != 3) {
        printf("Invalid input. Require exactly two string inputs\n");
        return 1;
    }
     
    
    char *seps = argv[1];
    //test vars getting stored correctly
    //printf("%s\n",seps);
    char *string = argv[2];
    //printf("%s\n",string);
      
       
    //char *seps = "";
    //char *string = "You have to print out hex of \a";
    //char *seps = "\\\\";
    //char *string = "\\\\\\hello\\\\\\world\\\\";
    //char *seps = "mn";
    //char *string = "manaa";
    TokenizerT *stream = TKCreate(seps, string);
    
    output(stream,strlen(stream->tokens));
  

  return 0;
}
