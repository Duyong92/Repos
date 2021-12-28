/*bin 경로에 있는 디렉토리 파일들을 확인한다.
world 데이터베이스를 MariaDB에 생성한다.
world 데이터베이스가 MariaDB에 생성되었다면 MariaDB에 접속한다.*/

/*MariaDB를 이용한 CRUD 실습*/
USE world;

/*
1.DISTINCT 연산자
SELECT DISTINCT 컬럼명1,컬럼명1,.. from 테이블명 where 조건절
*/ 

/*예제1-1
국가코드가 'KOR'인 도시들의 국가코드를 표시*/
SELECT CountryCode FROM city WHERE CountryCode='KOR';

/*예제1-2
국가코드가 'KOR'인 도시들의 국가코드를 중복제거해서 표시*/
SELECT DISTINCT CountryCode FROM city WHERE CountryCode='KOR';

/*
2.논리연산자(AND,OR,NOT)
SELECT * from 테이블명 where (not) 조건1 and/or (not) 조건2 ...
*/ 

/*예제2-1
국가코드가 'KOR'이면서 인구가 100만 이상인 도시*/
SELECT * FROM city WHERE CountryCode='KOR' AND Population >= 1000000;

/*예제2-2
국가코드가 'KOR','CHN',JPN'인 도시*/
SELECT * FROM city WHERE CountryCode='KOR' or CountryCode='CHN' or CountryCode='JPN';

/*예제2-3
국가코드가 'KOR'이 아니면서 인구가 100만 이상인 도시*/
SELECT * FROM city WHERE CountryCode!='KOR' AND Population >= 1000000;

/*예제2-4
국가코드가 'KOR'이 아니면서 인구가 100만 이상인 도시
ANSI/ISO 표준 부정논리 연산자 <>*/
SELECT * FROM city WHERE CountryCode <> 'KOR' AND Population >= 1000000;

/*
3.논리연산자(IN,BETWEEN)
영어(IN,BETWEEN)로 표현하는 것도 가능
*/ 

/*예제3-1
국가코드가 'KOR','CHN',JPN'인 도시*/
SELECT * FROM city WHERE CountryCode IN ('KOR','CHN','JPN');

/*예제3-2
국가코드가 'KOR'이고 인구가 100만 이상 500만 이하인 도시*/
SELECT * FROM city WHERE CountryCode = 'KOR' AND (Population BETWEEN 1000000 AND 5000000);

SELECT * FROM city WHERE CountryCode = 'KOR' AND (Population >= 1000000 AND Population <= 5000000);

/*
4.결과정렬(ORDER BY)
SELECT * from 테이블명 where 조건절 order by 컬럼명 asc/desc, ...
*/ 

/*예제4-1
국가코드가 'KOR'인 도시를 찾아 인구수의 역순으로 표시하시오.*/
SELECT * FROM city WHERE CountryCode = 'KOR' ORDER BY Population DESC;

/*예제4-2
city 테이블에서 국가코드와 인구수를 출력하라.
정렬은 쿡가코드별로 오름차순으로, 동일한 코드(국가) 안에서는 인구수의 역순으로 표시하시오.*/
SELECT CountryCode, Population FROM city ORDER BY CountryCode ASC, Population DESC;