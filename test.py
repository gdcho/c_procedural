import re

def process_large_responses(filename):
    # Prepare the output filename
    output_filename = 'bytes_' + filename

    # Initialize counters
    large_response_count = 0
    total_bytes = 0

    # Compile a regular expression to extract the bytes field from each log entry
    log_entry_regex = re.compile(r'.*HTTP/1.[01]"\s+\d+\s+(\d+)$')

    # Attempt to open the input file and process each log entry
    try:
        with open(filename, 'r') as log_file:
            for line in log_file:
                match = log_entry_regex.match(line)
                if match:
                    bytes_sent = int(match.group(1))
                    if bytes_sent > 5000:
                        large_response_count += 1
                        total_bytes += bytes_sent
    except FileNotFoundError:
        print(f"The file {filename} does not exist.")
        return  # Exit the function early if the file is not found

    # Write the statistics to the output file
    with open(output_filename, 'w') as output_file:
        output_file.write(f'{large_response_count}\n')
        output_file.write(f'{total_bytes}\n')

# Example usage:
process_large_responses('hosts_access_log_00.txt')
