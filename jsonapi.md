# json api
## client requests:
### sgin_up
```json
{
    "request_type": "sign_up",
    "user": {
        "login": "qwewq",
        "password": "qwe"
    }
}
```
### sgin_in
```json
{
    "request_type": "sign_in",
    "user": {
        "login": "qwewq",
        "password": "qwe"
    }
}
```
### sign_out
```json
{
    "request_type": "sign_out"
}
```
### output_message
```json
{
    "request_type": "output_message",
    "sender": "1",
    "recipient": "3",
    "text": "123"
}
```
## server responses:
### sgin_up
```json
{
    "response_type": "sign_up",
    "status": "login_exists",
}

{
    "response_type": "sign_up",
    "status": "already_signed",
}

{
    "response_type": "sign_up",
    "status": "ok",
    "user": {
        "id": "1",
        "login": "login"
    }
}
```
### sgin_in
```json
{
    "response_type": "sign_in",
    "status": "login_not_exists",
}

{
    "response_type": "sign_in",
    "status": "password_incorrect",
}

{
    "response_type": "sign_in",
    "status": "already_signed",
}

{
    "response_type": "sign_in",
    "status": "ok",
    "user": {
        "id": "1",
        "login": "login"
    }
}
```
### output_message
```json
{
    "response_type": "output_message",
    "status": "ok",
    "text": "text"
}
```
## server requests:
### input_message
```json
{
    "request_type": "input_message",
    "sender": {
        "id": "1",
        "login": "login"
    },
    "text": "text",
}
```
## client responses:
### input_message
```json
{
    "response_type": "input_message",
    "status": "ok",
    "sender": "1",
    "recipient": "3",
    "text": "hello"
}
```
