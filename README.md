
## Clinic Management System

This program is a simple clinic management system written in C. It provides two main modes of operation: Admin Mode and User Mode. The functionality includes adding and editing patient records, reserving and canceling appointment slots, and viewing records and reservations.

### Features

1. **Admin Mode:**
   - Add new patients
   - Edit existing patient details
   - Reserve appointment slots
   - Cancel reservations

2. **User Mode:**
   - View patient records
   - View today's reservations

### Code Overview

- **Headers and Libraries:**
  - Includes standard libraries like `stdio.h`, `stdlib.h`, `stdbool.h`, and `string.h`.
  - Includes custom headers `stdtypes.h` and `LINKEDLIST.h`.

- **Constants:**
  - `MAX_SLOTS`: Defines the maximum number of available slots.
  - `MAX_INVALID_ATTEMPTS`: Defines the maximum number of invalid attempts before the program exits.

- **Function Prototypes:**
  - Functions for both admin and user functionalities, such as `add_patient`, `edit_patient`, `reserve_slot`, etc.

- **Global Variables:**
  - `reserved_slots`: An array to track the reservation status of slots.

- **Main Function:**
  - Handles the initial welcome message and mode selection.
  - Controls the program flow based on user input.

- **Admin Mode:**
  - Protected by a password.
  - Allows performing CRUD operations on patient records and managing reservations.

- **User Mode:**
  - Allows viewing patient records and today's reservations.

- **Utility Functions:**
  - `check_admin_password`: Validates admin password.
  - `get_valid_gender` and `get_valid_age`: Validate input for gender and age.
  - `display_available_slots`: Shows available appointment slots.
  - `view_patient_record` and `view_todays_reservations`: Display relevant information.

### Usage

1. **Compile the Program:**
   ```sh
   gcc -o clinic_management main.c
   ```

2. **Run the Program:**
   ```sh
   ./clinic_management
   ```

3. **Follow the On-Screen Instructions:**
   - Select between Admin and User modes.
   - Perform the desired operations as prompted.

### Notes

- Ensure that `stdtypes.h` and `LINKEDLIST.h` are included in your project.
- The default admin password is `1234`.
