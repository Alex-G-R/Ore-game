# Define the tile data as a list of bytes
tile_data = [
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x42,
    0x00, 0x00, 0x48, 0x42
]

# Number of tiles in the map (5x5)
num_tiles = 100 * 100

# Create the binary data
binary_data = tile_data * num_tiles

# Write the binary data to a file
with open('map.bin', 'wb') as file:
    file.write(bytearray(binary_data))

print("map.bin file has been created.")
