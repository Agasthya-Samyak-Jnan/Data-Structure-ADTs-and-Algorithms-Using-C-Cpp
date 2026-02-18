def quickselect (nums,start,end,n):

    if start<end:

        pivot = nums[end]
        i = start-1

        for j in range(start,end):
            if nums[j]<pivot :
                i += 1
                nums[i],nums[j] = nums[j],nums[i]
    
        i += 1
        nums[i],nums[end] = nums[end],nums[i]

        if n<i :
            quickselect(nums,start,i-1,n)
        elif n>i :
            quickselect(nums,i+1,end,n)
        
def main():

    nums = [20,1,-1,0,4,5,5]
    n = int(input())

    quickselect(nums,0,len(nums)-1,n)

    print(nums[n])

if __name__ == "__main__":
    main()
