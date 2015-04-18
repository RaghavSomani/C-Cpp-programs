mydata=read.csv("ds1.10.csv")
training_data = mydata[1:10000,]
testing_data  = mydata[10001:26733,]
z_testing     = mydata[10001:26733,][11]

library(class)
std_data=scale(mydata[,1:10])
training_data = std_data[1:10000,]
testing_data  = std_data[10001:26733,]
z_training     = mydata[1:10000,11]
knn_pred_z	  = knn(training_data,testing_data,z_training,3)
z_testing=as.vector(t(z_testing))
knn_pred_z=as.integer(as.vector(knn_pred_z))
result1=z_testing[knn_pred_z==1]
cat(mean(result1),'\n')
result2=knn_pred_z[z_testing==1]
cat(mean(result2),'\n')
cat("Misclassification : ",mean(z_testing!=knn_pred_z),"\n")