aws lambda create-function --function-name demo \
--role arn:aws:iam::186150431454:role/lambda-demo \
--runtime provided --timeout 15 --memory-size 128 \
--handler demo --zip-file fileb://demo.zip
