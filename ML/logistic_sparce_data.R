mydata=read.csv("ds1.10.csv")
NR = 26733
NRTR=10000
training_data = mydata[1:NRTR,]
testing_data  = mydata[(NRTR+1):dim(mydata)[1],]
z_testing     = mydata[11][(NRTR+1):NR,]
model         = glm(Z~X1+X2+X3+X4+X5+X6+X7+X8+X9+X10,data=training_data,family=binomial)
model_pred_probs = predict(model,testing_data,type="response")
model_pred_z     = rep(0,(NR-NRTR))
model_pred_z[model_pred_probs>mean(training_data[,11])]  =  1
result1=z_testing[model_pred_z==1]
cat(mean(result1),"\n")
result2=model_pred_z[z_testing==1]
cat(mean(result2),"\n")
cat("Misclassification : ",mean(z_testing!=model_pred_z),"\n")