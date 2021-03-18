import multiprocessing.pool as mpp
import sys

# code based on: https://stackoverflow.com/a/57364423/2856041


def istarmap(self, func, iterable, chunksize=1):
    # For Python >=3.8
    if sys.version_info[1] >= 8:
        self._check_running()
        if chunksize < 1:
            raise ValueError(
                "Chunksize must be 1+, not {0:n}".format(
                    chunksize))

        task_batches = mpp.Pool._get_tasks(func, iterable, chunksize)
        result = mpp.IMapIterator(self)
    # For Python <3.8
    else:
        if self._state != mpp.RUN:
            raise ValueError("Pool not running")

        if chunksize < 1:
            raise ValueError(
                "Chunksize must be 1+, not {0:n}".format(
                    chunksize))

    task_batches = mpp.Pool._get_tasks(func, iterable, chunksize)
    result = mpp.IMapIterator(self._cache)

    self._taskqueue.put(
        (
            self._guarded_task_generation(result._job,
                                          mpp.starmapstar,
                                          task_batches),
            result._set_length
        ))
    return (item for chunk in result for item in chunk)


# Adding custom function to multiprocessing.pool.Pool
mpp.Pool.istarmap = istarmap