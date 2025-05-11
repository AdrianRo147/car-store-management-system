# Car Store Management system

## Features

- File based database.
- Add/Remove/Update vehicle.
- Add/Remove/Update customer.
- Add/Remove/Update employee.
- Sell vehicle to customer (Each sold vehicle will have assigned customer to which was vehicle sold to and employee who sold the vehicle).
- Revert vehicle sale.
- Save vehicles, customers and employees into file with specific syntax.
- Load vehicles, customers and employees from file into application on start.

## OS support

- Linux, MacOS, Windows
- Fully tested on Arch Linux (Kernel: 6.12.3-arch1-1)

# Usage

- Build with `make build release` (or `make build debug` if you want to build with debug symbols).
- Run compiled binary with `./out [filename]`.
- `filename` - Optional paramter, if no parameter is specified, database file with name `database.db` will be used. This filename with be used for both reading and saving.
- After starting app you will see available categories you can choose by entering number into terminal.
- Application can be exited using number `4` in category menu.
- After selecting category you can choose from actions available for selected category.
- Every action can be canceled by entering `c` into terminal. In this case user will be returned to category selection.
- In some actions text, numbers and dates can be entered `e. g. updating vehicle`. In this case user might not want to update every item of vehicle. To make no changes, enter `'.'`.
- After selecting `4. Exit` in category menu, vehicles, customers and employees will be saved to database file. In case application is exited in other ways `e. g. close button in OS, killing it with task manager, ...` database file should be save too on OS supporting POSIX signals (Linux, MacOS), however, this is not guaranteed.

## Make targets

- `make build release` - Builds optimized binary (without debug symbols) into `./build/bin/out`
- `make build debug` - Builds debug binary (with debug symbols) into `./build/bin/out`
- `make memtest` - Run compiled binary in valgrind to find memory leaks
- `make clean` - Deletes `./build` folder

## File syntax

- Sections: `\beginFile\`, `\endFile\`, `\beginVehicle\`, `\endVehicle\`, `\beginCustomer\`, `\endCustomer\`, `\beginEmployee`, `\endEmployee`.
- File must begin with `\beginFile\` and end with `\endFile\`.
- Each vehicle, customer and employee must begin with its corresponding section (e. g. `\beginVehicle`) and end with its corresponding section (e. g. `\endVehicle`).
- Data in each section must be in specific order (described in example below).
- Vehicle, customer and employee cannot be combined (e. g. if we use `\beginVehile\`, then `\beginCustomer\` cannot be before `\endVehicle\`).
- Empty list can be defined using keyword `null`.
- List can be defined using following syntax: `[item1,item2]`.
- Boolean values must have values `yes/no`.

### File example

```
\beginFile                          - Begin of file

\beginVehicle                       - Begin of vehicle
0                                   - Vehicle ID
AUDI                                - Vehicle manufacturer
S7                                  - Vehicle model
123456789ABCDEFGH                   - VIN code of vehicle
22. 11. 1999                        - Date of manufaction of specific model
61480                               - Kilometers driven
22. 11. 2024                        - Date when was car added
no                                  - Was vehicle sold?
65535                               - ID of employee who sold vehicle
65535                               - ID of customer who bought vehicle
0. 0. 0                             - Date when vehicle was sold
\endVehicle                         - End of vehicle

\beginVehicle                       - Begin of vehicle
1                                   - Vehicle ID
BMW                                 - Vehicle manufacturer
M3                                  - Vehicle model
ABCDEFGH123456789                   - VIN code of vehicle
22. 11. 1999                        - Date of manufaction of specific model
61480                               - Kilometers driven
22. 11. 2024                        - Date when was car added
yes                                 - Was vehicle sold?
0                                   - ID of employee who sold vehicle
1                                   - ID of customer who bought vehicle
27. 12. 2024                        - Date when vehicle was sold
\endVehicle                         - End of vehicle

\beginVehicle                       - Begin of vehicle
2                                   - Vehicle ID
SKODA                               - Vehicle Manufacturer
FABIA                               - Vehicle model
FGHJKLASDOENC4156                   - VIN code of vehicle
22. 11. 1999                        - Date of manufaction of specific model
111470                              - Kilometers driven
22. 11. 2024                        - Date when was car added
yes                                 - Was vehicle sold?
2                                   - ID of employee who sold vehicle
2                                   - ID of customer who bought vehicle
12. 12. 2024                        - Date when vehicle was sold
\endVehicle                         - End of vehicle

\beginVehicle                       - Begin of vehicle
3                                   - Vehicle ID
TOYOTA                              - Vehicle Manufacturer
YARIS                               - Vehicle model
FGHJASKSDOENC4156                   - VIN code of vehicle
22. 11. 1999                        - Date of manufaction of specific model
111470                              - Kilometers driven
22. 11. 2024                        - Date when was car added
yes                                 - Was vehicle sold?
2                                   - ID of employee who sold vehicle
2                                   - ID of customer who bought vehicle
12. 12. 2024                        - Date when vehicle was sold
\endVehicle                         - End of vehicle

\beginCustomer                      - Begin of customer
0                                   - ID of customer
Name                                - First name of customer
Surname                             - Surname of customer
22. 11. 1999                        - Date of birth of customer
22. 11. 2024                        - Date of user creation
null                                - List of bought vehicles
\endCustomer                        - End of customer

\beginCustomer                      - Begin of customer
1                                   - ID of customer
Name2                               - First name of customer
Surname2                            - Surname of customer
22. 11. 1999                        - Date of birth of customer
22. 11. 2024                        - Date of user creation
1                                   - List of bought vehicles
\endCustomer                        - End of customer

\beginCustomer                      - Begin of customer
2                                   - ID of customer
Name3                               - First name of customer
Surname3                            - Surname of customer
22. 11. 1999                        - Date of birth of customer
22. 11. 2024                        - Date of user creation
[2,3]                               - List of bought vehicles
\endCustomer                        - End of customer

\beginEmployee                      - Begin of employee
0                                   - ID of employee
Name4                               - First name of employee
Surname4                            - Surname of employee
12. 12. 1994                        - Date of birth of employee
12. 12. 2024                        - Date when was employee added
12. 12. 2025                        - Date until which is employee employed
1                                   - List of sold vehicles
\endEmployee                        - End of employee

\beginEmployee                      - Begin of employee
1                                   - ID of employee
Name5                               - First name of employee
Surname5                            - Surname of employee
12. 12. 1994                        - Date of birth of employee
12. 12. 2024                        - Date when was employee added
12. 12. 2025                        - Date until which is employee employed
null                                - List of sold vehicles
\endEmployee                        - End of employee

\beginEmployee                      - Begin of employee
2                                   - ID of employee
Name6                               - First name of employee
Surname6                            - Surname of employee
12. 12. 1994                        - Date of birth of employee
12. 12. 2024                        - Date when was employee added
12. 12. 2025                        - Date until which is employee employed
[2,3]                               - List of sold vehicles
\endEmployee                        - End of employee

\endFile                            - End of file
```

## Vehicle actions

### Print all vehicles

### Print specific vehicle

- User will be asked to enter ID of vehicle that has to be printed

### Add vehicle

- User will be asked for vehicle details

### Remove vehicle

- User will be asked for ID of vehicle that has to be removed
- NOTE: If vehicle was already sold, sale of specific vehicle will be reverted, affecting customer/employee that bought/sold vehicle

### Update vehicle

- User will be asked for ID of vehicle
- After entering ID, user will be asked for new vehicle details
- In case user don't want to change every details of vehicle, user has to enter '.' on specific detail when asked

### Sell vehicle

- User will asked for vehicle ID, ID of customer that bought vehicle and ID of employee that sold vehicle

### Revert vehicle sale

- This action reverts vehicle sale and affects customer/employee that bought/sold specific vehicle in order database won't get corrupted
- User will be asked for ID of vehicle

## Customer actions

### Print all customers

### Print specific customer

- User will be asked to enter ID of customer that has to be printed

### Add customer

- User will be asked for customer details

### Remove customer

- User will be asked for ID of customer that has to be removed
- NOTE: If customer has bought any vehicles, all bought vehicle sales will be reverted. This will affect every bought vehicles and employees that sold the vehicles

### Update customer

- User will be asked for ID of customer
- After entering ID, user will be asked for new customer details
- In case user don't want to change every details of customer, user has to enter '.' on specific detail when asked

## Employee actions

### Print all employees

### Print specific employee

- User will be asked to enter ID of employee that has to be printed

### Add employee

- User will be asked for employee details

### Remove employee

- User will be asked for ID of employee that has to be removed
- NOTE: If employee has sold any vehicles, all sold vehicle sales will be reverted. This will affect every sold vehicles and customers that bought the vehicles
