-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get crime details by querying crime scene reports table
SELECT "description" FROM "crime_scene_reports"
WHERE "street" = "Humphrey Street"
AND "month" = 7
AND "day" = 28;

/*
+--------------------------------------------------------------+
|                         description                          |
+--------------------------------------------------------------+
| Theft of the CS50 duck took place at 10:15am at the Humphrey |
|  Street bakery. Interviews were conducted today with three w |
| itnesses who were present at the time – each of their interv |
| iew transcripts mentions the bakery.                         |
+--------------------------------------------------------------+
| Littering took place at 16:36. No known witnesses.           |
+--------------------------------------------------------------+
*/


-- Get witnesses transcript
SELECT transcript FROM "interviews"
WHERE "month" = 7 
AND "day" = 28
AND "transcript" LIKE "%bakery%";


/*
+--------------------------------------------------------------+
|                          transcript                          |
+--------------------------------------------------------------+
| Sometime within ten minutes of the theft, I saw the thief ge |
| t into a car in the bakery parking lot and drive away. If yo |
| u have security footage from the bakery parking lot, you mig |
| ht want to look for cars that left the parking lot in that t |
| ime frame.                                                   |
+--------------------------------------------------------------+
| I don't know the thief's name, but it was someone I recogniz |
| ed. Earlier this morning, before I arrived at Emma's bakery, |
|  I was walking by the ATM on Leggett Street and saw the thie |
| f there withdrawing some money.                              |
+--------------------------------------------------------------+
| As the thief was leaving the bakery, they called someone who |
|  talked to them for less than a minute. In the call, I heard |
|  the thief say that they were planning to take the earliest  |
| flight out of Fiftyville tomorrow. The thief then asked the  |
| person on the other end of the phone to purchase the flight  |
| ticket.                                                      |
+--------------------------------------------------------------+
*/


-- Get names of people left parking using license plate
SELECT people.name From people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
AND (bakery_security_logs.hour BETWEEN 10 AND 11)
AND bakery_security_logs.activity = "exit";

/*
+---------+
|  name   |
+---------+
| Vanessa |
| Bruce   |
| Barry   |
| Luca    |
| Sofia   |
| Iman    |
| Diana   |
| Kelsey  |
| Taylor  |
+---------+
*/

-- Get people who withdraw money from Leggett street atm
SELECT people.name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.day = 28
AND atm_transactions.month = 7
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";

/*
+---------+
|  name   |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |
+---------+
*/

-- Get people who made phone calls less than a minute on that day
SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.day = 28 
AND phone_calls.month = 7 
AND phone_calls.duration < 60;

/*
+---------+
|  name   |
+---------+
| Sofia   |
| Kelsey  |
| Bruce   |
| Kelsey  |
| Taylor  |
| Diana   |
| Carina  |
| Kenny   |
| Benista |
+---------+
*/

-- Get the accomplice on the other side of the  phone  call
SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.day = 28 
AND phone_calls.month = 7 
AND phone_calls.duration < 60;

/*
+------------+
|    name    |
+------------+
| Jack       |
| Larry      |
| Robin      |
| Melissa    |
| James      |
| Philip     |
| Jacqueline |
| Doris      |
| Anna       |
+------------+
*/

-- Knowing first flight leaving fiftyville
SELECT id FROM flights
WHERE origin_airport_id= (
    SELECT id FROM airports 
    WHERE city="Fiftyville"
) 
AND "day" = 29 
ORDER BY "hour", "minute" 
LIMIT 1;

/*
+----+
| id |
+----+
| 36 |
+----+
*/

-- First flight depart to this destination
SELECT city  FROM airports 
WHERE airports.id = (
    SELECT destination_airport_id FROM flights 
    WHERE id = 36
);

/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
*/

-- People leaving in first flight
SELECT people.name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number 
WHERE passengers.flight_id = (
    SELECT id FROM flights 
    WHERE origin_airport_id= (
        SELECT id FROM airports 
        WHERE city= "Fiftyville") 
    AND "day" = 29 
    ORDER BY "hour", "minute" 
    LIMIT 1
);

/*
+--------+
|  name  |
+--------+
| Doris  |
| Sofia  |
| Bruce  |
| Edward |
| Kelsey |
| Taylor |
| Kenny  |
| Luca   |
+--------+
*/

-- Narrowing suspicious
SELECT people.name FROM people 
JOIN passengers ON people.passport_number = passengers.passport_number 
    AND passengers.flight_id = 36
JOIN phone_calls  ON people.phone_number = phone_calls.caller 
    AND phone_calls.day = 28 
    AND phone_calls.duration < 60
JOIN bakery_security_logs  ON people.license_plate = bakery_security_logs.license_plate 
    AND bakery_security_logs.day = 28 
    AND bakery_security_logs.activity = 'exit' 
    AND bakery_security_logs.hour = 10 
    AND bakery_security_logs.minute > 15 
    AND bakery_security_logs.minute < 25
JOIN bank_accounts  ON people.id = bank_accounts.person_id
JOIN atm_transactions  ON bank_accounts.account_number = atm_transactions.account_number 
    AND atm_transactions.transaction_type = 'withdraw' 
    AND atm_transactions.day = 28 
    AND atm_transactions.atm_location = 'Leggett Street';

/*
+-------+
| name  |
+-------+
| Bruce |
+-------+
*/


-- Get the accomplice
SELECT "name" FROM people 
WHERE phone_number IN (
    SELECT receiver FROM phone_calls 
    WHERE "day" = 28 
    AND duration < 60 
    AND "caller" = (
        SELECT phone_number FROM people 
        WHERE name="Bruce"
    )
);
/*
+-------+
| name  |
+-------+
| Robin |
+-------+
*/
