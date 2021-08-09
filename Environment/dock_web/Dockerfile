FROM python:3.7-alpine
EXPOSE 5000

RUN pip install pipenv
RUN mkdir -p /app/src

WORKDIR /app
ADD Pipfile /app
ADD Pipfile.lock /app
ADD src/index.py /app/src

RUN pipenv install --system --deploy --ignore-pipfile
CMD ["python", "/app/src/index.py"]

