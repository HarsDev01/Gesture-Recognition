import numpy as np
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.ensemble import RandomForestClassifier  # Use RandomForestClassifier instead of KNeighborsClassifier
from micromlgen import port

# Load the generated synthetic gesture data
data = pd.read_csv('synthetic_gesture_data.csv')  # Ensure the file exists

# Prepare the feature and label data
features = data[['AX', 'AY', 'AZ', 'GX', 'GY', 'GZ']].values
labels = data['Gesture'].values

# Encode the labels (gestures) to integer values
label_encoder = LabelEncoder()
encoded_labels = label_encoder.fit_transform(labels)

# Train a RandomForest classifier (a supported classifier in micromlgen)
model = RandomForestClassifier(n_estimators=100)
model.fit(features, encoded_labels)

# Convert the label encoder classes to a dictionary
classmap = {i: label for i, label in enumerate(label_encoder.classes_)}

# Export the model to C++ code (using micromlgen)
c_code = port(model, classmap=classmap)

# Save the C++ model code to a file
with open('model.h', 'w') as file:
    file.write(c_code)

print("Model exported successfully to 'model.h'!")
