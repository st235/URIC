# URIC

A Uniform Resource Identifier (URI) implementation in `C++`, designed strictly in compliance with [RFC 3986](https://datatracker.ietf.org/doc/html/rfc3986).

The library also includes an implementation of Uniform Resource Locator (URL) rules, which are a subset of URI rules. This implementation follows [the `MDN` definition of URL]((https://developer.mozilla.org/en-US/docs/Learn/Common_questions/Web_mechanics/What_is_a_URL)), specifically:

> Parameters
> `?key1=value1&key2=value2` are extra parameters provided to the Web server. Those parameters are a list of key/value pairs separated with the & symbol. The Web server can use those parameters to do extra stuff before returning the resource. Each Web server has its own rules regarding parameters, and the only reliable way to know if a specific Web server is handling parameters is by asking the Web server owner.

The library was tested with [`Raspberry Pi Pico and Pico W`](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html).

>[!NOTE]
>In the event that RFC 3986 is unavailable, please refer to the [local copy](./rfc3986.pdf).

## Bringing Dependencies

To install the library, which is utilizes CMake, follow these simple steps: 

first, include the FetchContent module in your CMake configuration. Then, declare the library by specifying the `git` repository and branch. Finally, make the content available and link the library to your target. Here’s a sample CMake snippet for reference:

```cmake
include(FetchContent)

FetchContent_Declare(
  URIC
  GIT_REPOSITORY git@github.com:st235/URIC.git
  GIT_TAG "main"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
)
FetchContent_MakeAvailable(URIC)

target_link_libraries(uri-validator uric)
```

## API

Using the API is really straightforward. Here’s a quick example to get you started:

First, parse the URI using `uri::Uri::parse(uri)`. If the URI is invalid, you'll get `std::nullopt` object. If it’s valid, you can easily access different parts of the URI. For example, you can get the scheme, authority, and other components.

Here’s a code snippet (from [samples](./samples/)) to illustrate:

```cpp
const auto& uri_opt = uri::Uri::parse(uri_to_verify);
if (!uri_opt) {
    std::cout << "Not a valid URI."  << std::endl;
    return 0;
}

const auto& uri = uri_opt.value();

if (uri.getScheme()) {
    std::cout << "Scheme: " << uri.getScheme().value() << std::endl;
}

if (uri.getAuthority()) {
    const auto& authority = uri.getAuthority().value();

    std::cout << "Authority:" << std::endl;
    if (authority.getUserInfo()) {
        std::cout << "\tUser Info: " << authority.getUserInfo().value() << std::endl;
    }

    std::cout << "\tHost: " << authority.getHost() << std::endl;

    if (authority.getPort()) {
        std::cout << "\tPort: " << authority.getPort().value() << std::endl;
    }
}
```

### Grammar

>[!NOTE]
> URI Grammar for future reference, see `RFC 3986` for more details.

```text
URI           = scheme ":" hier-part [ "?" query ] [ "#" fragment ]

   hier-part     = "//" authority path-abempty
                 / path-absolute
                 / path-rootless
                 / path-empty

   URI-reference = URI / relative-ref

   absolute-URI  = scheme ":" hier-part [ "?" query ]

   relative-ref  = relative-part [ "?" query ] [ "#" fragment ]

   relative-part = "//" authority path-abempty
                 / path-absolute
                 / path-noscheme
                 / path-empty

   scheme        = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )

   authority     = [ userinfo "@" ] host [ ":" port ]
   userinfo      = *( unreserved / pct-encoded / sub-delims / ":" )
   host          = IP-literal / IPv4address / reg-name
   port          = *DIGIT

   IP-literal    = "[" ( IPv6address / IPvFuture  ) "]"

   IPvFuture     = "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )

   IPv6address   =                            6( h16 ":" ) ls32
                 /                       "::" 5( h16 ":" ) ls32
                 / [               h16 ] "::" 4( h16 ":" ) ls32
                 / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
                 / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
                 / [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
                 / [ *4( h16 ":" ) h16 ] "::"              ls32
                 / [ *5( h16 ":" ) h16 ] "::"              h16
                 / [ *6( h16 ":" ) h16 ] "::"

   h16           = 1*4HEXDIG
   ls32          = ( h16 ":" h16 ) / IPv4address
   IPv4address   = dec-octet "." dec-octet "." dec-octet "." dec-octet

   dec-octet     = DIGIT                 ; 0-9
                 / %x31-39 DIGIT         ; 10-99
                 / "1" 2DIGIT            ; 100-199
                 / "2" %x30-34 DIGIT     ; 200-249
                 / "25" %x30-35          ; 250-255

   reg-name      = *( unreserved / pct-encoded / sub-delims )

   path          = path-abempty    ; begins with "/" or is empty
                 / path-absolute   ; begins with "/" but not "//"
                 / path-noscheme   ; begins with a non-colon segment
                 / path-rootless   ; begins with a segment
                 / path-empty      ; zero characters

   path-abempty  = *( "/" segment )
   path-absolute = "/" [ segment-nz *( "/" segment ) ]
   path-noscheme = segment-nz-nc *( "/" segment )
   path-rootless = segment-nz *( "/" segment )
   path-empty    = 0<pchar>

   segment       = *pchar
   segment-nz    = 1*pchar
   segment-nz-nc = 1*( unreserved / pct-encoded / sub-delims / "@" )
                 ; non-zero-length segment without any colon ":"

   pchar         = unreserved / pct-encoded / sub-delims / ":" / "@"

   query         = *( pchar / "/" / "?" )

   fragment      = *( pchar / "/" / "?" )

   pct-encoded   = "%" HEXDIG HEXDIG

   unreserved    = ALPHA / DIGIT / "-" / "." / "_" / "~"
   reserved      = gen-delims / sub-delims
   gen-delims    = ":" / "/" / "?" / "#" / "[" / "]" / "@"
   sub-delims    = "!" / "$" / "&" / "'" / "(" / ")"
                 / "*" / "+" / "," / ";" / "="
```

## Building the project

Use these commands to build the project:

```bash
mkdir build
cmake ..
make
```

### Running test

A lot of logic in the library heavily relies on _unit_ tests.
To run them you need yo _successfully build the project_ and run the command below:

```bash
ctest --output-on-failure [-R filter regex]
```
