library(ISLR)
attach(Smarket)
summary(Smarket)
cor(Smarket[-9])
training = (Year < 2005)
testing = !training
training_data = Smarket[training,]
testing_data = Smarket[testing,]
Direction_testing=Direction[testing]
stock_model=glm(Direction ~ Lag1+Lag2+Lag3+Lag4+Lag5+Volume, data=training_data, family=binomial)
summary(stock_model)
model_pred_probs = predict(stock_model, testing_data, type="response")
model_pred_Direction=rep("Down",252)
model_pred_Direction[model_pred_probs>0.5]="Up"
table(model_pred_Direction,Direction_testing)
mean(model_pred_Direction!=Direction_testing)