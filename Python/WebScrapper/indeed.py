import requests
from bs4 import BeautifulSoup
from requests.models import LocationParseError
LIMIT = 50
URL = f"https://www.indeed.com/jobs?q=python&limit={LIMIT}"
def get_last_page():
    result = requests.get(URL)
    soup = BeautifulSoup(result.text, "html.parser")

    pagination = soup.find("div", {"class": "pagination"})

    links = pagination.find_all('a')

    pages = []
    for link in links[:-1]:
        pages.append(int(link.string))

    last_page = pages[-1]

    return last_page

def extract_job(soupResult):

    title = soupResult.find("h2", {"class": "title"})
    title = title.find("a")["title"]

    company = soupResult.find("span", {"class": "company"})
    company_anchor = company.find("a")
    if company_anchor is not None:
        company = str((company_anchor.string))
    else:
         company = str((company.string))
    company = company.strip()

    location = soupResult.find("div", {"class": "recJobLoc"})["data-rc-loc"]
    job_id = soupResult["data-jk"]
    return {'title': title, 
            'company': company, 
            'location': location, 
            'link': f"https://www.indeed.com/viewjob?jk={job_id}"
    }


def extract_jobs(last_page):
    jobs = []
    for page in range(last_page):
        print(f"Scrapping page {page+1} in indeed")

        eachPage = requests.get(f"{URL}&start={LIMIT*page}")
        
        soup = BeautifulSoup(eachPage.text, "html.parser")
        soupResults = soup.find_all("div", {"class": "jobsearch-SerpJobCard"})
        
        for soupResult in soupResults:
            job = extract_job(soupResult)
            jobs.append(job)

    return jobs

def indeed_result():
    last_page = get_last_page()

    result = extract_jobs(last_page)

    return result