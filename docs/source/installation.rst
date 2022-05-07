Installation
============

MARTA supports out-of-tree execution. This method could be
preferred in order to avoid copying files, for instance, in an already
existent project.

Out-of-tree
-----------

Install a pre-built package (if any) or build the wheel and install it:

.. code-block:: bash

    cd MARTA
    python -m build
    python -m pip install dist/<marta-wheel>
    # or just
    python -m pip install <marta-wheel>


This will install a module named ``marta``, and two console scripts or CLI commands:
``marta_profiler`` and ``marta_analyzer``. **NOTE**: to run these commands it is needed
to specify in ``PATH`` variable the path where your Python version install
applications, e.g. ``export PATH=$PATH:$HOME/.local/bin`` if your Python
distribution install packages in ``$HOME/.local/bin``.

Use from the sources
--------------------

If you just want to use MARTA as a module this can be done easily by just:

.. code-block:: bash

    cd MARTA/marta
    python -m profiler ...
    # or
    python -m analyzer ...
