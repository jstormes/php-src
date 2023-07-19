## SAPI for Lambda in AWS (EXPERIMENTAL)

Implementation of PHP for AWS Lambda

## Disclaimer
This project is based on the work of Paulo Miguel Almeida's C work on [PauloMigAlmeida/aws-lambda-c-runtime](https://github.com/PauloMigAlmeida/aws-lambda-c-runtime),
witch itself is based on Marco Magdy's nice work on the [awslabs/aws-lambda-cpp](https://github.com/awslabs/aws-lambda-cpp)
repository.

Documentation and packaging mechanisms have been either adapted,ported or copied since I agree with most of the development
decisions made for the Aws Lambda C Runtime witch was based on the Lambda Cpp runtime.
Hence, all the credits should go to the AWS' guys.

## Design Goals
1. Negligible cold-start overhead.
2. To use PHP in a common fashion, as a templating engine.

## First time deployment
Create an IAM role and the Lambda function via the AWS CLI.

First create the following trust policy JSON file

```
$ cat trust-policy.json
{
 "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": {
        "Service": ["lambda.amazonaws.com"]
      },
      "Action": "sts:AssumeRole"
    }
  ]
}
```

Then create the IAM role:

```bash
$ aws iam create-role --role-name lambda-demo --assume-role-policy-document file://trust-policy.json
```

Note down the role Arn returned to you after running that command. We'll need it in the next steps:

Attach the following policy to allow Lambda to write logs in CloudWatch:
```bash
$ aws iam attach-role-policy --role-name lambda-demo --policy-arn arn:aws:iam::aws:policy/service-role/AWSLambdaBasicExecutionRole
```

Make sure you attach the appropriate policies and/or permissions for any other AWS services that you plan on using.

And finally, create the Lambda function:

```
$ aws lambda create-function --function-name demo \
--role <specify role arn from previous step here> \
--runtime provided --timeout 15 --memory-size 128 \
--handler demo --zip-file fileb://demo.zip
```

And to invoke the function:
```bash
$ aws lambda invoke --function-name demo --payload '{"my_cool_payload":"yay!"}' output.txt
```

NOTES: To package code
```bash
cd sapi/aws_lambda
./packaging/packager aws_lambda_php
mv aws_lambda_php.zip demo.zip
sh update
```
May need to `chmod u+x ./packaging/packager`



