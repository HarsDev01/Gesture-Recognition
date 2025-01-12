import numpy as np
import pandas as pd

# Number of samples for each gesture
num_samples = 100

# Generate synthetic data for 3 gestures
gestures = []
accelerometer_data = []
gyroscope_data = []

# Create synthetic data for each gesture
for gesture in range(1, 4):
    for _ in range(num_samples):
        # Generating synthetic accelerometer data (random values, you can adjust ranges)
        ax = np.random.randint(-2000, 2000)
        ay = np.random.randint(-2000, 2000)
        az = np.random.randint(15000, 17000)  # Simulate gravity-aligned Z-axis value

        # Generating synthetic gyroscope data (random values, adjust ranges)
        gx = np.random.randint(-1000, 1000)
        gy = np.random.randint(-1000, 1000)
        gz = np.random.randint(-1000, 1000)

        # Append the data for the current gesture
        accelerometer_data.append([ax, ay, az])
        gyroscope_data.append([gx, gy, gz])
        gestures.append(gesture)

# Combine all the data into a DataFrame
data = np.hstack([np.array(accelerometer_data), np.array(gyroscope_data), np.array(gestures).reshape(-1, 1)])

# Convert to a pandas DataFrame
columns = ['AX', 'AY', 'AZ', 'GX', 'GY', 'GZ', 'Gesture']
df = pd.DataFrame(data, columns=columns)

# Save the synthetic data to a CSV file
df.to_csv('synthetic_gesture_data.csv', index=False)

print("Synthetic data saved as 'synthetic_gesture_data.csv'!")
