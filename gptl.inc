      integer GPTLwall
      integer GPTLcpu
      integer GPTLabort_on_error

      parameter (GPTLwall           = 1)
      parameter (GPTLcpu            = 2)
      parameter (GPTLabort_on_error = 3)

! for compatibility with CAM entries

      integer wall
      integer usrsys
      parameter (wall = GPTLwall)
      parameter (usrsys = GPTLcpu)

! Externals

      integer gptlsetoption
      integer gptlinitialize
      integer gptlstart
      integer gptlstop
      integer gptlstamp 
      integer gptlpr
      integer gptlreset 
      integer gptlfinalize

      external gptlsetoption
      external gptlinitialize
      external gptlstart
      external gptlstop
      external gptlstamp 
      external gptlpr
      external gptlreset 
      external gptlfinalize