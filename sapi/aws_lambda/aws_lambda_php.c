//
// Created by jstormes on 7/14/23.
//

#include "aws_lambda_php.h"
#include "aws-lambda/c-runtime/runtime.h"

void my_handler(invocation_request *request, invocation_response **response){
//    *response = success(request->payload,"text/plain");
        *response = success("Hello World from AWS Lambda C Runtime for PHP","text/plain");
}

int main(int argc, char *argv[])
{
    run_handler(&my_handler);
    return 0;
}
