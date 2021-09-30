-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
FROM crime_scene_reports
WHERE day = "28"
AND month = "7"
AND year = "2020"
AND street = "Chamberlin Street"
--  transcripts from the interviews on the day of the crime
SELECT
    transcript
FROM
    interviews
WHERE
    day = "28"
    AND month = "7"
    AND year = "2020"
    AND transcript like "%courthouse%";
-- Get how the actvity is describe
/*
Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car
       in the courthouse parking lot and drive away. If you have security footage from
       the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning,
         before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw
         the thief there withdrawing some money.
Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
         In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
         The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/
WHERE name IN (SELECT name FROM phone_calls

JOIN people ON people.phone_number = phone_calls.caller

WHERE year = '2020' AND month = '7' AND day = '28' AND duration < '59')

AND name IN (SELECT name FROM courthouse_security_logs

JOIN people ON people.license_plate = courthouse_security_logs.license_plate

WHERE year = '2020' AND month = '7' AND day = '28' AND activity = 'exit' AND hour = 10 AND minute > 14 AND minute < 26)

AND name IN (SELECT name FROM passengers

JOIN people ON people.passport_number = passengers.passport_number

WHERE flight_id = '36')

AND name IN (SELECT name FROM atm_transactions

JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number

JOIN people ON bank_accounts.person_id = people.id

WHERE year = '2020' AND month = '7' AND day = '28' AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw');