#include <iostream>
#include <cpr/cpr.h>

void test_get();
void test_post1();
void test_post2();

int main() {
    test_get();
    test_post1();
    test_post2();

    return 0;
}

void test_get()
{
    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/libcpr/cpr/contributors"},
                               cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                               cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    std::cout << r.status_code << std::endl;                  // 200
    std::cout << r.header["content-type"] << std::endl;       // application/json; charset=utf-8
    std::cout << r.text << std::endl;
}

void test_post1()
{
    cpr::Response r = cpr::Post(cpr::Url{"http://www.httpbin.org/post"},
                                cpr::Body{"This is raw POST data"},
                                cpr::Header{{"Content-Type", "text/plain"}});
    std::cout << r.text << std::endl;

/*
 * {
 *   "args": {},
 *   "data": "This is raw POST data",
 *   "files": {},
 *   "form": {},
 *   "headers": {
 *     ..
 *     "Content-Type": "text/plain",
 *     ..
 *   },
 *   "json": null,
 *   "url": "http://www.httpbin.org/post"
 * }
 */
}

void test_post2()
{
    cpr::Response r = cpr::Post(cpr::Url{"http://www.httpbin.org/post"},
                                cpr::Payload{{"key", "value"}});
    std::cout << r.text << std::endl;

/*
 * {
 *   "args": {},
 *   "data": "",
 *   "files": {},
 *   "form": {
 *     "key": "value"
 *   },
 *   "headers": {
 *     ..
 *     "Content-Type": "application/x-www-form-urlencoded",
 *     ..
 *   },
 *   "json": null,
 *   "url": "http://www.httpbin.org/post"
 * }
 */
}