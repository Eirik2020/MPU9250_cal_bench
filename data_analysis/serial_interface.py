import serial
import struct

def decode_message(message):
    """
    Decode a message with the format:
    [Start] [Address] [Number of Payloads] [Payload] [End]
    Combines high and low bytes for accelerometer and gyroscope data.
    """
    # Ensure the message is long enough
    if len(message) < 13:  # 1 start + 1 address + 1 size + 12 data + 1 end
        print(len(message))
        raise ValueError("Message is too short to decode.")

    # Extract fields
    start = message[0]
    address = message[1]
    num_payloads = message[2]
    payload = message[3:-1]
    end = message[-1]

    # Validate the message structure
    if len(payload) != num_payloads:
        raise ValueError("Payload size does not match the number of payloads.")

        # Combine high and low bytes to form 16-bit signed integers
    try:
        ax = int.from_bytes(payload[0:2], byteorder='big', signed=True)
        ay = int.from_bytes(payload[2:4], byteorder='big', signed=True)
        az = int.from_bytes(payload[4:6], byteorder='big', signed=True)

        gx = int.from_bytes(payload[6:8], byteorder='big', signed=True)
        gy = int.from_bytes(payload[8:10], byteorder='big', signed=True)
        gz = int.from_bytes(payload[10:12], byteorder='big', signed=True)
    except Exception as e:
        print(f"Error decoding payload: {e}")
        return None

    return {
        "Start": start,
        "Address": address,
        "Accelerometer": {"ax": ax, "ay": ay, "az": az},
        "Gyroscope": {"gx": gx, "gy": gy, "gz": gz},
        "End": end
    }

def main():
    # Configure the serial port (update with your settings)
    ser = serial.Serial(
        port='COM7',       # Change to the correct COM port
        baudrate=115200,     # Match the device baud rate
        timeout=1          # Timeout in seconds
    )

    try:
        while True:
            # Read a line of input
            raw_data = ser.read_until(b'\x7F')  # Assuming 0x03 (ETX) is the End byte
            if raw_data:
                print("Raw data:", raw_data)

                # Decode the message
                try:
                    decoded_message = decode_message(raw_data)
                    print("Decoded Message:")
                    print(f"  Accelerometer: {decoded_message['Accelerometer']}")
                    print(f"  Gyroscope: {decoded_message['Gyroscope']}")
                    print("")
                    print("")
                except ValueError as e:
                    print("Error decoding message:", e)

    except KeyboardInterrupt:
        print("Exiting...")

    finally:
        ser.close()

if __name__ == "__main__":
    main()
