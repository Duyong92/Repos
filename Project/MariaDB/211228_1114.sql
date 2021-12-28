/*bin 경로에 있는 디렉토리 파일들을 확인한다.
world 데이터베이스를 MariaDB에 생성한다.
world 데이터베이스가 MariaDB에 생성되었다면 MariaDB에 접속한다.*/

/*MariaDB를 이용한 CRUD 실습*/
USE world;

SHOW TABLES;

DESC city;

/*SELECT 명령문
SELECT 컬럼명 FROM 테이블명 WHERE 조건절;*/
SELECT NAME FROM city WHERE Population >= 10000000;

/*INSERT INTO 명령문
INSERT INTO 테이블명(컬럼명) VALUES(값)*/
INSERT INTO city VALUES(20000, 'SampleCity2', 'KOR', 'Seoul', 2000000);

SELECT * FROM city WHERE id=20000;

/*UPDATE 명령문
UPDATE 테이블명 SET 컬럼명=값, ... WHERE 조건절;*/
UPDATE city SET Population=3000000 WHERE id=20000;

SELECT * FROM city WHERE id=20000;

/*DELETE 명령문
DELETE FROM 테이블명 WHERE 조건절;*/
DELETE FROM city WHERE id=20000;

SELECT *FROM city WHERE id=20000;