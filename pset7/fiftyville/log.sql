-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 2020年7月28日の犯罪現場報告から説明を選択します。
SELECT description FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28;

-- 12:04に破壊行為。目撃者なし。                                                                                                                                                                                |
-- | 万引きは03:01に発生。目撃者2名。                                                                                                                                                                  |
-- | 午前10時15分、チェンバリン・ストリートの裁判所においてCS50アヒルが盗まれた。本日、その場に居合わせた3人の目撃者から事情聴取が行われ、それぞれの事情聴取記録には裁判所について言及されている。|
-- | マネーロンダリングは20:30に行われた。目撃者は不明。                                                                                                                                                                         |
-- | ポイ捨ては16時36分に行われた。目撃者なし。    

-- 裁判所について言及している2020年7月28日のインタビューの書き起こしを選択します。
SELECT transcript FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28
AND transcript LIKE "%courthouse%";

-- 窃盗から10分以内に、泥棒が裁判所の駐車場で車に乗り込み、走り去るのを見た。もし裁判所の駐車場の監視カメラの映像があれば、その時間帯に駐車場から出た車を探すといいかもしれない。                                                     |
-- | 泥棒の名前は知らないが、見覚えのある人物だった。今朝早く、裁判所に到着する前に、フィファー通りのATMのそばを歩いていたら、そこで泥棒がお金を下ろしているのを見た。                                                                                                     |
-- | 泥棒が裁判所を出るとき、誰かに電話をかけて、1分もしないうちに話をした。その電話の中で、泥棒が「明日、フィフティビルを出る一番早い便に乗るつもりだ」と言っているのが聞こえた。そして窃盗犯は電話の相手に航空券を買うように頼んだ。

-- 2020年7月28日、午前10時15分から10時25分の間に裁判所を出た人々の活動、ナンバープレート、名前を取得します。
SELECT courthouse_security_logs.activity, courthouse_security_logs.license_plate, people.name FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate 
WHERE courthouse_security_logs.year = 2020 
AND courthouse_security_logs.month = 7 
AND courthouse_security_logs.day = 28
AND courthouse_security_logs.hour = 10
AND courthouse_security_logs.minute >=15
AND courthouse_security_logs.minute <= 25;

-- +----------+---------------+-----------+
-- | activity | license_plate |   name    |
-- +----------+---------------+-----------+
-- | exit     | 5P2BI95       | Patrick   |
-- | exit     | 94KL13X       | Ernest    |
-- | exit     | 6P58WS2       | Amber     |
-- | exit     | 4328GD8       | Danielle  |
-- | exit     | G412CB7       | Roger     |
-- | exit     | L93JTIZ       | Elizabeth |
-- | exit     | 322W7JE       | Russell   |
-- | exit     | 0NTHK55       | Evelyn    |
-- +----------+---------------+-----------+

-- Fifer StreetのATMで2020年7月28日に引き出しを行った人々の名前と取引タイプを取得します。
SELECT people.name, atm_transactions.transaction_type FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id 
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2020
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_location = 'Fifer Street'
AND atm_transactions.transaction_type = 'withdraw';

-- +-----------+------------------+
-- |   name    | transaction_type |
-- +-----------+------------------+
-- | Ernest    | withdraw         |
-- | Russell   | withdraw         |
-- | Roy       | withdraw         |
-- | Bobby     | withdraw         |
-- | Elizabeth | withdraw         |
-- | Danielle  | withdraw         |
-- | Madison   | withdraw         |
-- | Victoria  | withdraw         |
-- +-----------+------------------+

-- 電話の記録に発信者の名前を設定します。
UPDATE phone_calls
SET caller_name = people.name
FROM people
WHERE phone_calls.caller = people.phone_number;

-- 電話の記録に受信者の名前を設定します。
UPDATE phone_calls
SET receiver_name = people.name
FROM people
WHERE phone_calls.receiver = people.phone_number;

-- 2020年7月28日に60秒未満の通話を行った発信者と受信者の情報を取得します。
SELECT caller, caller_name, receiver, receiver_name FROM phone_calls
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60;

-- +----------------+-------------+----------------+---------------+
-- |     caller     | caller_name |    receiver    | receiver_name |
-- +----------------+-------------+----------------+---------------+
-- | (130) 555-0289 | Roger       | (996) 555-8899 | Jack          |
-- | (499) 555-9472 | Evelyn      | (892) 555-8872 | Larry         |
-- | (367) 555-5533 | Ernest      | (375) 555-8161 | Berthold      |
-- | (499) 555-9472 | Evelyn      | (717) 555-1342 | Melissa       |
-- | (286) 555-6063 | Madison     | (676) 555-6554 | James         |
-- | (770) 555-1861 | Russell     | (725) 555-3243 | Philip        |
-- | (031) 555-6622 | Kimberly    | (910) 555-3251 | Jacqueline    |
-- | (826) 555-1652 | Bobby       | (066) 555-9701 | Doris         |
-- | (338) 555-6650 | Victoria    | (704) 555-2131 | Anna          |
-- +----------------+-------------+----------------+---------------+

-- 'Fiftyville'という都市の空港のIDを取得します。
SELECT id FROM airports
WHERE city = 'Fiftyville';
-- +----+
-- | id |
-- +----+
-- | 8  |
-- +----+

-- 2020年7月29日にFiftyvilleから出発する最初のフライトの詳細を取得します。
SELECT id, hour, minute, origin_airport_id, destination_airport_id 
FROM flights
WHERE year = 2020
AND month = 7
AND day = 29
AND origin_airport_id = 8
ORDER BY hour ASC
LIMIT 1;

-- +----+------+--------+-------------------+------------------------+
-- | id | hour | minute | origin_airport_id | destination_airport_id |
-- +----+------+--------+-------------------+------------------------+
-- | 36 | 8    | 20     | 8                 | 4                      |
-- +----+------+--------+-------------------+------------------------+

-- IDが4の空港の都市を取得します。
SELECT city FROM airports
WHERE id = 4;

-- +--------+
-- |  city  |
-- +--------+
-- | London |
-- +--------+

-- フライトIDが27のフライトの目的地、名前、電話番号、ナンバープレートを持つ乗客を取得します。
SELECT flights.destination_airport_id, name, phone_number, license_plate from people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id = 27
ORDER BY flights.hour ASC;

-- +------------------------+-----------+----------------+---------------+
-- | destination_airport_id |   name    |  phone_number  | license_plate |
-- +------------------------+-----------+----------------+---------------+
-- | 8                      | Mark      | (873) 555-3868 | YD7376W       |
-- | 8                      | Keith     | (209) 555-7806 | 630U2R7       |
-- | 8                      | Amy       | (670) 555-8598 | NULL          |
-- | 8                      | Jeremy    | (194) 555-5027 | V47T75I       |
-- | 8                      | Diana     | (918) 555-2946 | P743G7C       |
-- | 8                      | Walter    | (544) 555-8087 | 82456Y8       |
-- | 8                      | Stephanie | (204) 555-4136 | 2001OV9       |
-- +------------------------+-----------+----------------+---------------+

-- 特定の条件に一致する人物の名前を取得します。これには、特定の日に特定の場所での活動、短い電話、ATMの引き出し、および特定のフライトへの搭乗が含まれます。
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE (flights.year = 2020 AND flights.month = 7 AND flights.day = 29 AND flights.id = 36)
AND name IN
(SELECT phone_calls.caller_name FROM phone_calls
WHERE year = 2020
AND month = 7
AND day = 28
AND duration < 60)
AND name IN
(SELECT people.name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id 
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2020
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_location = 'Fifer Street'
AND atm_transactions.transaction_type = 'withdraw')
AND name IN
(SELECT people.name FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate 
WHERE courthouse_security_logs.year = 2020 
AND courthouse_security_logs.month = 7 
AND courthouse_security_logs.day = 28
AND courthouse_security_logs.hour = 10
AND courthouse_security_logs.minute >=15
AND courthouse_security_logs.minute <= 25);

-- +--------+
-- |  name  |
-- +--------+
-- | Ernest |
-- +--------+

