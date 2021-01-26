from indeed import indeed_result
from so import StackOverFlow_result
from save import save_to_file

indeed_jobs = indeed_result()
stackoverflow_jobs = StackOverFlow_result()
jobs = indeed_jobs + stackoverflow_jobs
save_to_file(jobs)