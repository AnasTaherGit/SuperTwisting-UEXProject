function [p, r] = calculatePitchRoll()

    % This function reads acceleration and angular velocity from an IMU sensor
    % and calculates its orientation by finding out pitch and roll. In this
    % application MPU9250 sensor is used. However, it could be replaced with
    % any other IMU sensor as well.

    persistent arduinoObj imuObj
    persistent prevTimestamp
    persistent pitchAngle rollAngle
    persistent pitchAccelOffset rollAccelOffset pitchGyroOffset rollGyroOffset

    % Output
    r = 0;
    p = 0;

    if isempty(arduinoObj)
        arduinoObj = arduino();
    end

    if isempty(imuObj)
        imuObj = mpu6050(arduinoObj,'SamplesPerRead',1);
    end

    % x -> longitudinal axis or N axis or roll axis
    % y -> transverse axis or E axis or pitch axis
    % z -> vertical axis or  D axis or yaw axis
    if isempty(pitchAccelOffset)
        pitchAccelOffset = 0;
        pitchGyroOffset = 0;
        rollAccelOffset = 0;
        rollGyroOffset = 0;
        prevTimestamp = 0;

        % Calculate the average offset error produced by accelerometer and gyroscope.
        count = 100;

        for i = 1:count

            if i == count
                accel = imuObj.readAcceleration;
                gyro = imuObj.readAngularVelocity;
                timestamp = cputime;
                prevTimestamp = timestamp;
            else
                accel = imuObj.readAcceleration;
                gyro = imuObj.readAngularVelocity;
            end

            pitchAccelOffset = pitchAccelOffset + atan2(accel(1), sqrt(accel(2) * accel(2) + accel(3) * accel(3)));
            rollAccelOffset = rollAccelOffset + atan2(-accel(2), sqrt(accel(1) * accel(1) + accel(3) * accel(3)));
            pitchGyroOffset = pitchGyroOffset + gyro(2);
            rollGyroOffset = rollGyroOffset + gyro(1);
        end

        pitchAccelOffset = pitchAccelOffset / count;
        rollAccelOffset = rollAccelOffset / count;
        pitchGyroOffset = pitchGyroOffset / count;
        rollGyroOffset = rollGyroOffset / count;
    end

    if isempty(pitchAngle)
        pitchAngle = 0;
    end

    if isempty(rollAngle)
        rollAngle = 0;
    end

    % Using complementary filter to fuse accelerometer and gyroscope data.
    % Filter coefficient should be tuned to improve result
    filterCoeff = 0.98;

    accel = imuObj.readAcceleration;
    gyro = imuObj.readAngularVelocity;
    timestamp = cputime;
    % Calculate pitch and roll from acceleration values and remove offset
    accelPitchAngle = atan2(accel(1), sqrt(accel(2) * accel(2) + accel(3) * accel(3))) - pitchAccelOffset;
    accelRollAngle = atan2(-accel(2), sqrt(accel(1) * accel(1) + accel(3) * accel(3))) - rollAccelOffset;
    % Subtract the offset values calculated at the beginning
    gyro(1) = gyro(1) - rollGyroOffset;
    gyro(2) = gyro(2) - pitchGyroOffset;
    gyroPitchAngleDiff = gyro(2) * (timestamp - prevTimestamp);
    gyroRollAngleDiff = gyro(1) * (timestamp - prevTimestamp);

    % Use complementary filter to fuse accelerometer and gyroscope data
    pitchAngle = filterCoeff * (pitchAngle + gyroPitchAngleDiff) + (1 - filterCoeff) * accelPitchAngle;
    rollAngle = filterCoeff * (rollAngle + gyroRollAngleDiff) + (1 - filterCoeff) * accelRollAngle;

    % sensor object returns angular velocity in radians/s. Converting pitch and
    % roll angles into degree
    p = pitchAngle * 180 / pi;
    r = rollAngle * 180 / pi;
