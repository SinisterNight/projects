# Import the required packages
import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.utils import shuffle
from sklearn.svm import SVR
from sklearn.metrics import confusion_matrix, classification_report, mean_squared_error, explained_variance_score

# Load the housing dataset and shuffle the data so that you don't bias your analysis.
data = datasets.load_boston()
X, y = shuffle(data.data, data.target, random_state=7)

# Split the dataset into training and testing in an 80/20 format:
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=7)

# Create and train the Support Vector Regressor using a linear kernel.
sv_regressor = SVR(kernel='linear')
sv_regressor.fit(X_train, y_train)

# Run the regressor on the testing data and predict the output (predicted labels).
y_test_pred = sv_regressor.predict(X_test)

# Evaluate the performance of the regressor and print the initial metrics.
mse = mean_squared_error(y_test, y_test_pred)
evs = explained_variance_score(y_test, y_test_pred)
print("Mean Squared Error:", mse)
print("Explained Variance Score:", evs)

# Binarize the predicted values & the actual values using threshold of 25.00.
y_pred_label = np.where(y_test_pred > 25.00, 1, 0)
y_test_label = np.where(y_test > 25.00, 1, 0)

# Create the confusion matrix using the predicted labels and the actual labels.
confusion_mat = confusion_matrix(y_test_label, y_pred_label)

# Visualize the confusion matrix.
plt.imshow(confusion_mat, interpolation='nearest', cmap=plt.cm.gray)
plt.title('Confusion matrix')
plt.colorbar()
ticks = np.arange(2)
plt.xticks(ticks, ticks)
plt.yticks(ticks, ticks)
plt.ylabel('True labels')
plt.xlabel('Predicted labels')
plt.show()

# Print the classification report based on the confusion matrix.
classification_rep = classification_report(y_test_label, y_pred_label)
print("Classification Report:\n", classification_rep)
