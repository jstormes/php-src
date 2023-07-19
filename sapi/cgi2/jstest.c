//
// Created by jstormes on 7/12/23.
//
#include "aws-lambda/c-runtime/runtime.h"

void my_handler(invocation_request *request, invocation_response **response){
//    if(rand() == 42)
//        *response = failure("Hello World from AWS Lambda C Runtime","Application_Error");
//    else
//char *t = request->payload;
    *response = success(request->payload,"text/plain");
//        *response = success("Hello World from AWS Lambda C Runtime take two","text/plain");
}

int main2(void){
    run_handler(&my_handler);
    return 0;
}